/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:54 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/03 13:56:04 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		exit_cmd(t_env *env, const char *cmd, const char **args)
{
    (void)cmd;
	(void)args;
	(void)env;
	printf("exit\n");
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
