/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:54 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/25 14:41:54 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	if (env->pipex_stack.total_item > 1)
		return (0);
	return (EXIT_MINISHELL);
}
