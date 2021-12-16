/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/12/16 17:11:28 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_pipex_stack_int(t_env *env, t_list_double *action)
{
	t_cell_pipex	*current_cell;
	if (!action)
		return ;
	current_cell = action->content;
	// (*fun)(env, *(int *)action->content);
	select_right_cmd(env, current_cell->args[0], (const char**)current_cell->args);
	execute_pipex_stack_int(env, action->next);
}

void	execute_pipex_stack(t_env *env)
{
	execute_pipex_stack_int(env, env->pipex_stack.head);
}
