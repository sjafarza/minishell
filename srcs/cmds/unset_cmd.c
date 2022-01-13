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

int	unset_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;
	int	r;

	(void)cmd;
	(void)env;
	if (!args[1])
		return (-EXIT_FAILURE);
	i = 0;
	while (args[++i])
	{
		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
			printf("minshell: unset:( %s ): not valid identifier\n", args[i]);
		r = del_env_var(env, (char *)args[i]);
	}
	if (!r)
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
