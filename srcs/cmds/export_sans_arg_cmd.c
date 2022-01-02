/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sans_arg_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:51:37 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/18 19:52:51 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_sans_arg_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;

	(void)cmd;
	(void)env;
	if (args[1])
		return (-EXIT_FAILURE);
	i = 0;
	while (i < env->env_vars_max)
	{
		printf("declare -x %s=[%s]\n", env->env_vars[i].name.str, \
			env->env_vars[i].value.str);
		i++;
	}
	return (EXIT_SUCCESS);
}
