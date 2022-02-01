/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2022/02/01 21:30:00 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		return (-EXIT_FAILURE);
	if (w_ret == last_pid)
	{
		if (WIFEXITED(d_status))
		{
			env->exit_value = WEXITSTATUS(d_status);
			g_status = env->exit_value;
			str_exit_value = ft_itoa(env->exit_value);
			if (!str_exit_value)
				return (-EXIT_FAILURE);
			find_and_update_env_var(env, "?", str_exit_value);
		}
	}
	return (EXIT_SUCCESS);
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
