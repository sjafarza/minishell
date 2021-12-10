/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_groups_stack_exe.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 18:54:29 by scarboni          #+#    #+#             */
/*   Updated: 2021/12/10 22:40:53 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_parsed_groups_stack_int(t_env *env, t_list_double *action)
{
	if (!action)
		return ;
	// (*fun)(env, *(int *)action->content);
	execute_parsed_groups_stack_int(env, action->next);
}

void	execute_parsed_groups_stack(t_env *env)
{
	execute_parsed_groups_stack_int(env, env->pipex_stack.head);
}
