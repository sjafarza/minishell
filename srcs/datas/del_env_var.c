/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:14:02 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/24 22:29:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	move_env_vars_array_content(t_env_var *src
, t_env_var *dst, int len)
{
	return (move_env_vars_array_content_from_i_until_max(src, dst, 0, len));
}

int	move_env_vars_array_content_from_i_until_max(t_env_var *src
, t_env_var *dst, int i, int max)
{
	if (!src | !dst)
		return (-EXIT_FAILURE);
	while (i < max)
	{
		dst[i] = src[i];
		src[i] = (t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	fill_tmp_env_vars_array_without_one_var(t_env_var *src
, t_env_var *dst, t_str var_name, int max)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!var_name.str | !dst | !src | max < 0)
		return (-EXIT_FAILURE);
	while (i < max)
	{
		if (src[i].name.len == var_name.len && ft_strncmp(src[i].name.str,
				var_name.str, src[i].name.len) == 0)
		{	
			free_one_var(src[i]);
			src[i++] = (t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
		}
		else
		{
			dst[j] = src[i];
			src[i] = (t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
			j++;
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	del_env_var(t_env *env, char *var_name)
{
	t_env_var	*tmp_env_vars;
	int			tmp_env_v_max;

	if (!var_name)
		return (-EXIT_FAILURE);
	if (!find_env_vars(env, var_name))
		return (EXIT_SUCCESS);
	tmp_env_v_max = env->env_vars_max - 1;
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_v_max);
	if (!tmp_env_vars)
		return (-EXIT_FAILURE);
	if (fill_tmp_env_vars_array_without_one_var(env->env_vars, tmp_env_vars,
			(t_str){var_name, ft_strlen(var_name)}, env->env_vars_max)
			== -EXIT_FAILURE)
	{
		free(tmp_env_vars);
		return (-EXIT_FAILURE);
	}
	clean_env_vars(env);
	env->env_vars = tmp_env_vars;
	env->env_vars_max = tmp_env_v_max;
	return (EXIT_SUCCESS);
}
