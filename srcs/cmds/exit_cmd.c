/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:54 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/16 22:40:16 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exit_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	if (env->pipex_stack.total_item > 1)
		return (EXIT_SUCCESS);
	return (EXIT_MINISHELL);
}
