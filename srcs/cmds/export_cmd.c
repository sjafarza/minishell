/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 20:18:27 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int		i;
	int		k;
	char	*name;
	char	*value;

	(void)cmd;
	i = 0;
	k = -1;
	while (args[++i])
	{
		if (produce_name_value((char *)args[i], &name, &value) == -EXIT_FAILURE)
		{		
			printf("2minshell:export:(%s): not valid identifier\n", args[i]);
			return (-EXIT_FAILURE);
		}
		while (name[++k])
		{
			if (ft_is_valid_for_env_var_name(name[k]) == 0)
			{		
				printf("2minshell:export:(%s=%s): not valid identifier\n", name, value);
				free(name);
				free(value);
				return (-EXIT_FAILURE);
			}
		}
		if ((ft_strlen(name) == PATH_LEN) && (ft_strncmp(name, PATH_STR, PATH_LEN) == 0) && init_path(env) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
		if (find_and_update_env_var(env, name, value) == EXIT_SUCCESS)
			free(name);
		else if (add_new_env_by_value_name(env, name, value) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
