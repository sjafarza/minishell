/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/31 17:14:07 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_cell_pipex(void *v_cell)
{
	t_cell_pipex	*cell;

	cell = (t_cell_pipex *)v_cell;
	if (cell->args)
		free_array(cell->args);
	clear_io_stack(&(cell->io_stack));
	free(cell);
}

void	clear_pipex_stack(t_env *env)
{
	ft_lstdbclear(&env->pipex_stack.head, &free_cell_pipex);
	env->pipex_stack.total_item = 0;
	env->pipex_stack.tail = NULL;
}

static int	add_back_pipex_stack_int(t_env *env, t_cell_pipex *content)
{
	env->pipex_stack.tail = ft_lstdbnew(content);
	if (!env->pipex_stack.tail)
	{
		free(content);
		return (-EXIT_FAILURE);
	}
	ft_lstdbadd_back(&env->pipex_stack.head, env->pipex_stack.tail);
	env->pipex_stack.total_item++;
	return (EXIT_SUCCESS);
}

int	add_back_pipex_stack(t_env *env, char **args, t_stack io_stack)
{
	t_cell_pipex	*content;
	t_list_double	*previous_tail;

	if (!args || io_stack.total_item == -1)
		return (-EXIT_FAILURE);
	content = (t_cell_pipex *)malloc(sizeof(t_cell_pipex));
	if (!content)
		return (-EXIT_FAILURE);
	content->args = args;
	content->child_pid = 0;
	content->io_stack = io_stack;
	content->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	content->pipe_to_next[ID_CURRENT_NODE_SIDE] = -1;
	previous_tail = env->pipex_stack.tail;
	if (add_back_pipex_stack_int(env, content) == EXIT_FAILURE)
		return (-EXIT_FAILURE);
	env->pipex_stack.tail->prev = previous_tail;
	return (EXIT_SUCCESS);
}
