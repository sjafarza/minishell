/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/04 17:29:24 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		unset_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)env;
	if (!args[1])
		return (-EXIT_FAILURE);
	printf("I am in unset_cmd\n");
	//env = del_env_var(env, (char *)args[1]);	
	if (!del_env_var(env, (char *)args[1]))
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
