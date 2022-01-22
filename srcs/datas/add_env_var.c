/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 21:50:23 by scarboni         ###   ########.fr       */
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

int	add_new_env_by_value_name_raw(t_env *env, char *name, char *value, char *raw)
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
	env->env_vars[tmp_env_vars_max - 1] = (t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
	if (init_t_str(&env->env_vars[tmp_env_vars_max - 1].name, name) != EXIT_SUCCESS || init_t_str(&env->env_vars[tmp_env_vars_max - 1].value, value) != EXIT_SUCCESS)
	{
		free(tmp_env_vars);
		return (-EXIT_FAILURE);
	}
	init_t_str(&env->env_vars[tmp_env_vars_max - 1].raw, raw);
	env->env_vars_max = tmp_env_vars_max;
	if ((ft_strlen(name) == PATH_LEN) && (ft_strncmp(name, PATH_STR, PATH_LEN) == 0))
		return(init_path(env));	
	return (EXIT_SUCCESS);
}
