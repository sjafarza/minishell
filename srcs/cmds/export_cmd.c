/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2021/12/20 14:20:26 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int find_in_env(t_env *env, char *var)
{
	char	*name;
	char	*value;

	printf("var in FIND_IN_ENV = %s\n", var);
	value = ft_substr(var, find_first_eq(var), ft_strlen(var) - find_first_eq(var));
	if (value == NULL)
		value = "";
	printf("value  for SHLVL=  %s\n", value);	
	name = ft_substr(var, 0, find_first_eq(var) - 1);
	if (name == NULL)
		return(-EXIT_FAILURE);	
	if (ft_strlen(name) == 5 && (ft_strncmp(name, "SHLVL",5) == 0))	
		value = make_value(value);	
	printf(" CORECTION OF value  for SHLVL=  %s\n", value);	
	if (find_and_update_env_var(env, name, value) == EXIT_SUCCESS)
	{
		if ((ft_strlen(name) == 4) && (ft_strncmp(name, "PATH",4) == 0))
			{
				printf("il faudra qu'on mette a jour env->paths\n");
				//free(env->PATH);
				//env->PATH = fft_strdup(tmp[1]);
			}
		return (EXIT_SUCCESS);
	}
	return (-EXIT_FAILURE);
}

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;
printf("HELLO IN THERE\n");
	(void)cmd;
	(void)env;
	if (!args[1])
		printf("Must print env or Export \n");
		//return (-EXIT_FAILURE);	
	i = -1;
	while (args[++i])
	{
		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
		{
			if (args[i][0] == '=')
			{		
				printf("minishell: export: ( %s ): not a valid identifier\n", args[i]);
				return (-EXIT_FAILURE);
			}
			if (find_in_env(env, (char *)args[i]) == EXIT_SUCCESS)
				continue ;
			add_env_var(env, (char *)args[i]);
		}
			printf("INJA\n");
	}
	printf("2INJA\n");
	return (EXIT_SUCCESS);
}
