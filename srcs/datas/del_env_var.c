/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:14:02 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/29 12:53:46 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_str(t_str *obj, char *s)
{
	if (!obj)
		return (-EXIT_FAILURE);
	if (!s)
		s = " ";	
	obj->str = ft_strdup(s);
	obj->len = ft_strlen(s);
	return (EXIT_SUCCESS);
}

int	fill_tmp(t_env *env, t_env_var *tmp, char *var_name, int max)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	max = max + 1 -1;	
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == (int)ft_strlen(var_name) && \
				!ft_strncmp(env->env_vars[i].name.str, \
				var_name, ft_strlen(var_name)))
			i++;
		else
		{
			if (init_str(&tmp[j].name, env->env_vars[i].name.str) \
				!= EXIT_SUCCESS || init_str(&tmp[j].value, \
				env->env_vars[i].value.str) != EXIT_SUCCESS)
					return (-EXIT_FAILURE);
			j++;
			i++;
		}
	}
	tmp[j].name.str = "";
	tmp[j].value.str = "";
	return (EXIT_SUCCESS);
}

int	del_env_var(t_env *env, char *var_name)
{
	t_env_var	*tmp_env_vars;
	int			tmp_env_vars_max;

	if (!var_name)
		return (-EXIT_FAILURE);
	if(!find_env_vars(env, var_name))
		return (EXIT_SUCCESS);
	tmp_env_vars_max = env->env_vars_max;		
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!tmp_env_vars)
		return (-EXIT_FAILURE);
	/*if (!env->env_vars)
		return (-EXIT_FAILURE);*/
	if (fill_tmp(env, tmp_env_vars, var_name, tmp_env_vars_max) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);	
	clean_env_vars(env);	
	env->env_vars = tmp_env_vars;
	env->env_vars_max -= 1;
	return (EXIT_SUCCESS);
}
