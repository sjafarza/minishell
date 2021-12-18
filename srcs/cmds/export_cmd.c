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
		printf("Must print env\n");
		//return (-EXIT_FAILURE);
	i = -1;
	while (args[++i])
	{
		printf("** args[%d] = %s\n", i, args[i]);
		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
		{
			if (args[i][0] == '=')
			{		
				printf("minishell: export: ( %s ): not a valid identifier\n", args[i]);
				return (-EXIT_FAILURE);
			}
			printf("ok args[1] = %s for send to add_env_var\n", args[i]);
			int j = add_env_var(env, (char *)args[i]);
			printf("j in retun add-env-var = %d\n", j);
			return(j);
			//return (add_env_var(env, (char *)args[i]));
		}
	}
	return (EXIT_SUCCESS);
}
