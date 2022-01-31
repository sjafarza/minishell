/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/01/31 17:49:06 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define NO_CMD 42

void	try_dup2_or_die(t_env *env, int fd1, int fd2)
{
	int	res;

	res = dup2(fd1, fd2);
	if (fd1 < fd2)
		if (res != fd1)	
		{
			free_t_env(env);
			exit(1);
		}
	if (res != fd2)
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
		cell = (t_cell_pipex*)action->prev->content;
		if (cell->pipe_to_next[ID_NEXT_NODE_SIDE] != -1)
			close(cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
		cell->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	}
	cell = (t_cell_pipex*)action->content;
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
		cell = (t_cell_pipex*)action->prev->content;
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
	cell = (t_cell_pipex*)action->content;
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
	
	current_cell = (t_cell_pipex*)current->content;
	if (current_cell->pipe_to_next[ID_NEXT_NODE_SIDE] != -1)
		close(current_cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
	if (current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE] != -1)
		close(current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
	current_cell->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE] = -1;
	close_pipes_until(current->next, stop);
}

int	start_child(t_env *env, t_list_double *action, int id_cmd)
{
	pid_t			child_pid;
	int				exit_value;
	t_cell_pipex	*current_cell;

	current_cell = (t_cell_pipex*)action->content;
	close_pipes_until(env->pipex_stack.head, action->prev);
	if (action != env->pipex_stack.tail)
	{
		if (pipe(current_cell->pipe_to_next) == -EXIT_FAILURE)
		{
			printf("PIPEING FAILURE !!! \n");
			return (-EXIT_FAILURE);
		}
	else 
		printf("PIPE ALIVE\n");
	}
	child_pid = fork();
	if (child_pid < 0)
		return (-EXIT_FAILURE);
	if (child_pid == 0)
	{
		if (prepare_both_ends_of_processes(env, action) != EXIT_SUCCESS)
		{
			free_t_env(env);
			exit(1);
		}
		exit_value = execute_io_stack(env, &(current_cell->io_stack));
		if (exit_value != EXIT_SUCCESS)
		{
			free_t_env(env);
			exit(exit_value);
		}
		if (env->final_input_fd && *env->final_input_fd  >= 0)
			try_dup2_or_die(env, *env->final_input_fd, STDIN_FILENO);
		if (env->final_output_fd && *env->final_output_fd >= 0)
			try_dup2_or_die(env, *env->final_output_fd, STDOUT_FILENO);
		if (id_cmd == NO_CMD)
			exit_value = EXIT_SUCCESS;
		else
			exit_value = g_cmd_dictionary[id_cmd].fun(env,
					current_cell->args[0], (const char**)current_cell->args);
		free_t_env(env);
		exit(exit_value);
	}
	// close(current_cell->pipe_to_next[ID_NEXT_NODE_SIDE]);
	// current_cell->pipe_to_next[ID_NEXT_NODE_SIDE] = -1;
	// close(current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE]);
	// current_cell->pipe_to_next[ID_CURRENT_NODE_SIDE] = -1;
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
	last_pid = start_child_before_or_after(env, action);
	if (!action->next)
		return (last_pid);
	return (execute_pipex_stack_int(env, action->next));
}

t_list_double	*get_relevant_pipex_elem(t_env *env, int pid)
{
	t_list_double	*curent_elem;
	t_cell_pipex	*cell;

	curent_elem = env->pipex_stack.head;
	while (curent_elem)
	{
		cell = curent_elem->content;
		if (cell->child_pid == pid)
			return (curent_elem);
		curent_elem = curent_elem->next;
	}
	return (NULL);
}

int	ft_wait(int last_pid, t_env *env)
{
	int				w_ret;
	int				d_status;
	char			*str_exit_value;
	t_list_double	*exited_pipex_elem;

	w_ret = waitpid(-1, &d_status, WUNTRACED);
	exited_pipex_elem = get_relevant_pipex_elem(env, w_ret);
	if (exited_pipex_elem)
		close_pipe_after_use(exited_pipex_elem);
	else 
		printf("wtf\n");
	// if (w_ret == c1)
	// 	close(env->pipes_handles[ID_C1]);
	if (w_ret == last_pid)
	{
		if (WIFEXITED(d_status)){
			env->exit_value = WEXITSTATUS(d_status);
			str_exit_value = ft_itoa(env->exit_value);
			if (!str_exit_value)
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
