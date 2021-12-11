/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:14:02 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/07 13:22:44 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_str(t_str *obj, char *s)
{
	if (!obj || !s)
		return (-EXIT_FAILURE);
	obj->str = ft_strdup(s);
	obj->len = ft_strlen(s);
	return (EXIT_SUCCESS);
}

int	dup_tmp_to_env(t_env *env, t_env *tmp, int i)
{
	env->env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);	
	env->env_vars_max = tmp->env_vars_max;
	while (++i < env->env_vars_max)
		if (init_str(&env->env_vars[i].name, tmp->env_vars[i].name.str) \
			!= EXIT_SUCCESS || init_str(&env->env_vars[i].value, \
				tmp->env_vars[i].value.str) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
	env->env_vars[i].name.str = NULL;
	env->env_vars[i].value.str = NULL;
	init_path(env);
	init_cwd(env);
	return (EXIT_SUCCESS);
}

int	fill_tmp(t_env *env, t_env *tmp, char *var_name, int i)
{
	int	j;

	j = 0;
	tmp->env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == (int)ft_strlen(var_name) && \
				!ft_strncmp(env->env_vars[i].name.str, \
				var_name, ft_strlen(var_name)))
			i++;
		else
		{
			if (init_str(&tmp->env_vars[j].name, env->env_vars[i].name.str) \
				!= EXIT_SUCCESS || init_str(&tmp->env_vars[j].value, \
				env->env_vars[i].value.str) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
			j++;
			i++;
		}
	}
	tmp->env_vars[j].name.str = NULL;
	tmp->env_vars[j].value.str = NULL;
	return (EXIT_SUCCESS);
}

int	del_env_var(t_env *env, char *var_name)
{
	t_env	tmp;

	tmp = (t_env){0};
	if (!var_name)
		return (-EXIT_FAILURE);
	tmp.env_vars_max = env->env_vars_max - 1;
	if (fill_tmp(env, &tmp, var_name, 0) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	init_path(&tmp);
	init_cwd(&tmp);
	free_t_env(env);
	if (dup_tmp_to_env(env, &tmp, -1) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	free_t_env(&tmp);
	return (EXIT_SUCCESS);
}
