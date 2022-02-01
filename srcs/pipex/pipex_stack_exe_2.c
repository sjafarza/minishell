/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/02/01 13:01:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define NO_CMD 42

void	clean_exit(t_env *env, int code)
{
	free_t_env(env);
	exit(code);
}

void	prepare_io(t_env *env, t_list_double *action,
	t_cell_pipex *current_cell)
{
	int	exit_value;

	prepare_both_ends_of_processes(env, action);
	exit_value = execute_io_stack(env, &(current_cell->io_stack));
	if (exit_value != EXIT_SUCCESS)
		clean_exit(env, exit_value);
	if (env->final_input_fd && *env->final_input_fd >= 0)
		try_dup2_or_die(env, *env->final_input_fd, STDIN_FILENO);
	if (env->final_output_fd && *env->final_output_fd >= 0)
		try_dup2_or_die(env, *env->final_output_fd, STDOUT_FILENO);
}

int	start_child(t_env *env, t_list_double *action, int id_cmd)
{
	pid_t			child_pid;
	int				exit_value;
	t_cell_pipex	*current_cell;

	current_cell = (t_cell_pipex *)action->content;
	close_pipes_until(env->pipex_stack.head, action->prev);
	if (action != env->pipex_stack.tail)
		if (pipe(current_cell->pipe_to_next) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
	child_pid = fork();
	if (child_pid < 0)
		return (-EXIT_FAILURE);
	if (child_pid == 0)
	{
		prepare_io(env, action, current_cell);
		if (id_cmd == NO_CMD)
			exit_value = EXIT_SUCCESS;
		else
			exit_value = g_cmd_dictionary[id_cmd].fun(env,
					current_cell->args[0], (const char**)current_cell->args);
		clean_exit(env, exit_value);
	}
	current_cell->child_pid = child_pid;
	return (child_pid);
}

int	start_child_before_or_after(t_env *env, t_list_double *action)
{
	pid_t			child_pid;
	int				exit_value;
	int				id_cmd;
	t_cell_pipex	*current_cell;

	current_cell = (t_cell_pipex *)action->content;
	if (current_cell->args[0])
		id_cmd = select_right_cmd(current_cell->args[0],
				(const char **)current_cell->args);
	else
		id_cmd = NO_CMD;
	if (id_cmd == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (id_cmd == NO_CMD || g_cmd_dictionary[id_cmd].must_be_in_child)
		return (start_child(env, action, id_cmd));
	exit_value = g_cmd_dictionary[id_cmd].fun(env, current_cell->args[0],
			(const char **)current_cell->args);
	child_pid = fork();
	if (child_pid < 0)
		return (-EXIT_FAILURE);
	if (child_pid == 0)
		clean_exit(env, exit_value);
	current_cell->child_pid = child_pid;
	return (child_pid);
}
