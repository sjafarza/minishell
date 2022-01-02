/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2021/12/29 12:55:22 by saray            ###   ########.fr       */
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
		*value = "";
	return (EXIT_SUCCESS);
}

int	ft_add(t_env *env, char	*var)
{
	char		*value;
	char		*name;
	t_env_var	*tmp_env_vars;
	int			tmp_env_vars_max;

	if (produce_name_value(var, &name, &value) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	tmp_env_vars_max = env->env_vars_max + 1;
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);
	if (fill_tmp(env, tmp_env_vars, name, tmp_env_vars_max) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (init_str(&tmp_env_vars[tmp_env_vars_max - 1].name, name) \
	 	 != EXIT_SUCCESS || init_str(&tmp_env_vars[tmp_env_vars_max - 1] \
	 	.value, value) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	if ((ft_strlen(name) == 4) && (ft_strncmp(name, "PATH", 4) == 0))
		env->paths = ft_split(value, ':');
	clean_env_vars(env);
	env->env_vars = tmp_env_vars;
	env->env_vars_max += 1;
	free(name);
	free(value);
	return (EXIT_SUCCESS);
}

int	add_env_var(t_env *env, char *var)
{
	ft_add(env, var);
	return (EXIT_SUCCESS);
}
