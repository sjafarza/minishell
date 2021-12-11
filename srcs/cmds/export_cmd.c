/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 00:25:12 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;

	(void)cmd;
	(void)env;
	if (!args[1])
		return (-EXIT_FAILURE);
	i = -1;
	while (args[++i])
	{
		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
		{
			if (args[i][0] == '=')
			{		
				printf("minishell: export: << %s >> : \
						identifiant non valable\n", args[i]);
				return (-EXIT_FAILURE);
			}
			return (add_env_var(env, (char *)args[i]));
		}
	}
	return (EXIT_SUCCESS);
}
