/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2021/12/29 22:46:33 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_in_env(t_env *env, char *var)
{
	char	*name;
	char	*value;
	int		indx;

	indx = ft_strchr_index((const char *)var, '=');
	if (indx < 0)
		return (-EXIT_FAILURE);
	name = ft_substr(var, 0, indx);
	if (name == NULL)
		return (-EXIT_FAILURE);
	if (find_env_vars(env, name))
	{
		value = ft_substr(var, indx + 1, ft_strlen(var) - indx);
		if (value == NULL)
			value = "";
		if (find_and_update_env_var(env, name, value) == EXIT_SUCCESS)
		{
			if ((ft_strlen(name) == 4) && (ft_strncmp(name, "PATH", 4) == 0))
				env->paths = ft_split(value, ':');
			free (name);
			return (EXIT_SUCCESS);
		}
	}
	free (name);
	return (-EXIT_FAILURE);
}

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;

	(void)cmd;
	(void)env;
	i = -1;

	while (args[++i])
	{
		if (ft_strchr_index(args[i], '$') != -EXIT_FAILURE)
		{
			printf("minshell:export:(%s): not valid identifier\n", args[i]);
			return (-EXIT_FAILURE);
		}

		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
		{
			if (args[i][0] == '=' || args[i][0] == ' ' || args[i][0] == '?' || args[i][0] == '$')
			{		
				printf("minshell:export:(%s): not valid identifier\n", args[i]);
				return (-EXIT_FAILURE);
			}
			if (find_in_env(env, (char *)args[i]) == EXIT_SUCCESS)
				continue ;	
			add_env_var(env, (char *)args[i]);
		}
	}
	return (EXIT_SUCCESS);
}
