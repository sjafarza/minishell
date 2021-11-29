/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/29 11:46:36 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

#define NO_ARRAY -1

static int	get_array_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return NO_ARRAY;
	while (arr[i])
		i++;
	return (i);
}

int	init_env_vars(t_env *env, char **raw_env)
{
	int		i;
	int		separator_index;
	char	*name_tmp;
	char	*value_tmp;

	i = 0;
	env->env_vars_max = get_array_size(raw_env);
	if (env->env_vars_max == NO_ARRAY || env->env_vars_max == 0)
		return (-EXIT_FAILURE);
	env->env_vars_max++;
	env->env_vars = (t_env_var*)malloc(sizeof(t_env_var) * env->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);
	name_tmp = ft_strdup("?");
	value_tmp = ft_strdup("0");
	if (init_t_str(&env->env_vars[i].name, name_tmp) != EXIT_SUCCESS || init_t_str(&env->env_vars[i].value, value_tmp) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	i++;
	while (i < env->env_vars_max)
	{
		separator_index = ft_strchr_index(raw_env[i - 1], '=');
		if(separator_index < 0)
			return (-EXIT_FAILURE);
		name_tmp = ft_substr(raw_env[i - 1], 0, separator_index);
		value_tmp = ft_substr(raw_env[i - 1], separator_index + 1, ft_strlen(raw_env[i - 1]));
		if (init_t_str(&env->env_vars[i].name, name_tmp) != EXIT_SUCCESS || init_t_str(&env->env_vars[i].value, value_tmp) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
		i++;
	}
	// print_vars(env);
	return (EXIT_SUCCESS);
}
