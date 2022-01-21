/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2022/01/21 22:06:26 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	produce_name_value(char *var, char **name, char **value)
{
	int	indx;

	*name = NULL;
	*value = NULL;
	indx = ft_strchr_index((const char *)var, '=');
	if (indx < 0)
		return (-EXIT_FAILURE);
	*name = ft_substr(var, 0, indx);
	if (*name == NULL)
		return (-EXIT_FAILURE);
	*value = ft_substr(var, indx + 1, ft_strlen(var) - indx);
	if (*value == NULL)
	{
		free(*name);
		*name = NULL;
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	add_new_env_by_value_name(t_env *env, char *name, char *value)
{
	t_env_var	*tmp_env_vars;
	int			tmp_env_vars_max;

	if (!name | !value)
		return (-EXIT_FAILURE);
	tmp_env_vars_max = env->env_vars_max + 1;
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!tmp_env_vars)
		return (-EXIT_FAILURE);
	if (env->env_vars)
	{
		if (move_env_vars_array_content(env->env_vars, tmp_env_vars, env->env_vars_max) == -EXIT_FAILURE) /*fill_tmp_env_vars_array */
		{
			free(tmp_env_vars);
			return (-EXIT_FAILURE);
		}
		free(env->env_vars);
	}
	env->env_vars = tmp_env_vars;
	if (init_t_str(&env->env_vars[tmp_env_vars_max - 1].name, name) != EXIT_SUCCESS || init_t_str(&env->env_vars[tmp_env_vars_max - 1].value, value) != EXIT_SUCCESS)
	{
		free(tmp_env_vars);
		return (-EXIT_FAILURE);
	}
	if ((ft_strlen(name) == PATH_LEN) && (ft_strncmp(name, PATH_STR, PATH_LEN) == 0))
	{
		if (env->paths)
			free_array(env->paths);
		env->paths = ft_split(value, ':');
	}
	env->env_vars_max = tmp_env_vars_max;
	return (EXIT_SUCCESS);
}

static int	ft_add(t_env *env, char	*var)
{
	char		*value;
	char		*name;
	//t_env_var	*tmp_env_vars;
	//int			tmp_env_vars_max;

	if (produce_name_value(var, &name, &value) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (ft_strchr_index(name,'?') != -EXIT_FAILURE )
		{
			if (ft_strchr_index(value,'?') != -EXIT_FAILURE)
				printf("minshell:export:(%s=%s): not valid identifier\n", name, value);
			else
				printf("minshell:export:(%s): not valid identifier\n", name);
			free(name);
			free(value);
			return (-EXIT_FAILURE);
		}	
	//*****************************************	
	if(add_new_env_by_value_name(env, name, value) == -EXIT_FAILURE)
	{
		free(name);
		free(value);
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	add_env_var(t_env *env, char *var)
{
	return (ft_add(env, var));
}
