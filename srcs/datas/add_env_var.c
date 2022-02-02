/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2022/02/02 15:00:52 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	chek_alloc(char *name, char *value, \
		int tmp_env_vars_max, t_env_var **tmp_env_vars)
{
	if (!name | !value)
		return (-EXIT_FAILURE);
	*tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!(*tmp_env_vars))
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static	int	move_env(t_env *env, t_env_var *tm_env_var)
{
	if (env->env_vars)
	{
		if (move_env_vars_array_content(env->env_vars, \
			tm_env_var, env->env_vars_max) == -EXIT_FAILURE)
		{
			free(tm_env_var);
			return (-EXIT_FAILURE);
		}
		free(env->env_vars);
	}
	return (EXIT_SUCCESS);
}

static int	if_path_then_update(t_env *env, char *name)
{
	if (ft_strncmp(name, PATH_STR, PATH_LEN + 1) == 0)
		return (init_path(env));
	return (EXIT_SUCCESS);
}

int	add_new_env_by_value_name_raw(t_env *env,
		char *name, char *value, char *raw)
{
	t_env_var	*tm_env_var;
	int			tmp_env_vars_max;

	tmp_env_vars_max = env->env_vars_max + 1;
	if (chek_alloc(name, value, tmp_env_vars_max, &tm_env_var) == EXIT_SUCCESS)
	{
		if (move_env(env, tm_env_var) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
		env->env_vars = tm_env_var;
		env->env_vars[tmp_env_vars_max - 1] = \
			(t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
		if (init_t_str(&env->env_vars[tmp_env_vars_max - 1].name, name) != \
		EXIT_SUCCESS || init_t_str(&env->env_vars[tmp_env_vars_max - 1].\
			value, value) != EXIT_SUCCESS)
		{
			free(tm_env_var);
			return (-EXIT_FAILURE);
		}
		init_t_str(&env->env_vars[tmp_env_vars_max - 1].raw, raw);
		env->env_vars_max = tmp_env_vars_max;
		return (if_path_then_update(env, name));
	}
	return (-EXIT_FAILURE);
}
