/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/04 15:13:08 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	(void)env;
	print_vars(env);
	return (EXIT_SUCCESS);
}
