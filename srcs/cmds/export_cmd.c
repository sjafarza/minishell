/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 14:50:24 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*int     is_valid_as_env_var_name(const char *s)
{
        int     i;
        i = -1;
        while(s[++i])
        {
                if (!ft_isalnum(s[i]) && s[i] != '_' && s[i] != '=')
                        return (-EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}*/

int	find_in_env(t_env *env, char *var)
{
	char	*name;
	char	*value;
	int		indx;
	int		res;

	res = EXIT_SUCCESS;
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
				res = init_path(env);
			free (name);
			return (res);
		}
	}
	free (name);
	return (-EXIT_FAILURE);
}

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int		i;
	int		k;
	char	*name;
	char	*value;

	(void)cmd;
	(void)env;
	i = -1;
	k = -1;

	while (args[++i])
	{
		if (ft_strchr_index(args[i], '$') != -EXIT_FAILURE && ft_strlen(args[i]) == 1)
		{
			printf("1minshell:export:(%s): not valid identifier\n", args[i]);
			return (-EXIT_FAILURE);
		}
		if (ft_strchr_index(args[i], '=') != -EXIT_FAILURE)
		{
			if (ft_strncmp(args[i], "export",6) == 0)
				continue ;
			if (produce_name_value((char *)args[i], &name, &value) == -EXIT_FAILURE)
				return (-EXIT_FAILURE);
			while (name[++k])
			{
				if (!ft_is_valid_for_env_var_name(name[k]))
				{		
					printf("2minshell:export:(%s=%s): not valid identifier\n", name, value);
					free(name);
					free(value);
					return (-EXIT_FAILURE);
				}
			}
			if (find_in_env(env, (char *)args[i]) == EXIT_SUCCESS)
				continue ;		
			add_env_var(env, (char *)args[i]);
		}
		/*else if (is_valid_as_env_var_name(args[i]) && i != 0)
        {
            printf("4minshell:export:(%s): not valid identifier\n", args[i]);
            return (-EXIT_FAILURE);
        }*/
	}
	return (EXIT_SUCCESS);
}
