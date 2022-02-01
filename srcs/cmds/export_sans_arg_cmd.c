/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sans_arg_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 19:51:37 by sjafarza          #+#    #+#             */
/*   Updated: 2022/02/01 16:15:12 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_sans_arg_cmd(t_env *env, const char *cmd, const char **args,
	int silent)
{
	int	i;

	(void)cmd;
	if (args[1])
		return (1);
	if (silent == true)
		return (0);
	i = 0;
	while (i < env->env_vars_max)
	{
		printf("declare -x %s=[%s]\n", env->env_vars[i].name.str, \
			env->env_vars[i].value.str);
		i++;
	}
	return (0);
}
