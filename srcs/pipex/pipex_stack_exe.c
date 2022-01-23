/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/23 22:04:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define NO_CMD 42

int	start_child(t_env *env, t_cell_pipex *current_cell, int id_cmd)
{
	pid_t	child_pid;
	int		exit_value;

	child_pid = fork();
	if (child_pid < 0)
		return (-EXIT_FAILURE);
	if (child_pid == 0)
	{
		// dup2(current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE], STDOUT_FILENO);
		// close(current_cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
		execute_io_stack(env, &(current_cell->io_stack));
		if (id_cmd == NO_CMD)
			exit_value = EXIT_SUCCESS;
		else
			exit_value = g_cmd_dictionary[id_cmd].fun(env, current_cell->args[0], (const char**)current_cell->args);
		free_t_env(env);
		exit(exit_value);
	}
	// close(current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
	current_cell->child_pid = child_pid;
	return (child_pid);
}


	// dup2(pipex_cell->pipe_to_next[ID_CURRENT_NODE_SIDE], STDOUT_FILENO);
	// close(pipex_cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
	// dup2(next->pipex_cell->pipe_to_next[ID_NEXT_NODE_SIDE], STDIN_FILENO);
	// close(next->pipex_cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);

int	start_child_before_or_after(t_env *env, t_cell_pipex *current_cell)
{
	pid_t	child_pid;
	int		exit_value;
	int		id_cmd;
	
	if (current_cell->args[0])
		id_cmd = select_right_cmd(current_cell->args[0], (const char **)current_cell->args);
	else
		id_cmd = NO_CMD;
	if (id_cmd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);	
	if (id_cmd == NO_CMD || g_cmd_dictionary[id_cmd].must_be_in_child)
		return (start_child(env, current_cell, id_cmd));
	exit_value = g_cmd_dictionary[id_cmd].fun(env, current_cell->args[0], (const char**)current_cell->args);
	child_pid = fork();
	if (child_pid < 0)
		return (-EXIT_FAILURE);
	if (child_pid == 0)
	{
		free_t_env(env);
		exit(exit_value);
	}
	current_cell->child_pid = child_pid;
	return (child_pid);
}

static pid_t	execute_pipex_stack_int(t_env *env, t_list_double *action)
{
	pid_t				last_pid;
	if (!action)
		return (-EXIT_FAILURE);
	last_pid = start_child_before_or_after(env, action->content);
	if (!action->next)
		return (last_pid);
	//print_vars(env);
	return (execute_pipex_stack_int(env, action->next));
}

int	ft_wait(int last_pid, t_env *env)
{
	int		w_ret;
	int		d_status;
	char	*str_exit_value;

	w_ret = waitpid(-1, &d_status, WUNTRACED);
	// if (w_ret == c1)
	// 	close(env->pipes_handles[ID_C1]);
	if (w_ret == last_pid)
	{
		if (WIFEXITED(d_status)){
			env->exit_value = WEXITSTATUS(d_status);
			str_exit_value = ft_itoa(env->exit_value);
			if(!str_exit_value)
				return (-EXIT_FAILURE);
			find_and_update_env_var(env, "?", str_exit_value);
		}
		// close(env->pipes_handles[ID_C2]);
	}
	return (EXIT_SUCCESS);
}

int	execute_pipex_stack(t_env *env)
{
	pid_t	last_pid;
	int		count_awaited_childs;

	last_pid = execute_pipex_stack_int(env, env->pipex_stack.head);
	if (last_pid == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	count_awaited_childs = 0;
	while (count_awaited_childs < env->pipex_stack.total_item)
	{
		if (ft_wait(last_pid, env) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
		count_awaited_childs++;
	}
	return (EXIT_SUCCESS);
}
