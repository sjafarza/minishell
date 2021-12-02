/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_stack_exe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/30 14:04:56 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static void	execute_pipex_stack_int(t_env *env, t_list_double *action)
{
	if (!action)
		return ;
	// (*fun)(env, *(int *)action->content);
	execute_pipex_stack_int(env, action->next);
}

void	execute_pipex_stack(t_env *env)
{
	execute_pipex_stack_int(env, env->pipex_stack.head);
}
