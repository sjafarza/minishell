/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/31 18:01:55 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	try_dup2_or_die(t_env *env, int fd1, int fd2)
{
	int	res;

	res = dup2(fd1, fd2);
	if (res != fd2 && res != fd1)
	{
		free_t_env(env);
		exit(1);
	}
}

void	close_pipe_after_use(t_list_double *action)
{
	t_cell_pipex	*cell;

	if (action->prev)
	{
		cell = (t_cell_pipex *)action->prev->content;
		if (cell->pipe_to_next[ID_NEXT_NODE_SIDE] != -1)
			close(cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
		cell->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	}
	cell = (t_cell_pipex *)action->content;
	if (action->next)
	{
		if (cell->pipe_to_next[ID_CURRENT_NODE_SIDE] != -1)
			close(cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
		cell->pipe_to_next[ID_CURRENT_NODE_SIDE] = -1;
	}
}

int	prepare_both_ends_of_processes(t_env *env, t_list_double *action)
{
	t_cell_pipex	*cell;

	if (action->prev)
	{
		cell = (t_cell_pipex *)action->prev->content;
		if (!cell)
		{
			free_t_env(env);
			exit(1);
		}
		env->final_input_fd = &(cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
		if (cell->pipe_to_next[ID_CURRENT_NODE_SIDE] == -1)
			return (-EXIT_FAILURE);
		close(cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
	}
	cell = (t_cell_pipex *)action->content;
	if (action->next)
	{
		env->final_output_fd = &(cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
		if (cell->pipe_to_next[ID_NEXT_NODE_SIDE] == -1)
			return (-EXIT_FAILURE);
		close(cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
	}
	return (EXIT_SUCCESS);
}

void	close_pipes_until(t_list_double *current, t_list_double *stop)
{
	t_cell_pipex	*current_cell;

	if (!current | !stop | current == stop)
		return ;
	current_cell = (t_cell_pipex *)current->content;
	if (current_cell->pipe_to_next[ID_NEXT_NODE_SIDE] != -1)
		close(current_cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
	if (current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE] != -1)
		close(current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
	current_cell->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE] = -1;
	close_pipes_until(current->next, stop);
}
