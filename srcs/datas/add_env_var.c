/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 00:37:55 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_add(t_env *env, t_env *env_tmp, char	*var) 
{
	char	**tmp;
	int		m;

	tmp = ft_split(var, '=');
	if (!tmp)
		return (-EXIT_FAILURE);
	if (tmp[1] == NULL)
		tmp[1] = " ";	
	env_tmp->env_vars_max = env->env_vars_max + 1;
	m = env_tmp->env_vars_max - 1;
	if (fill_tmp(env, env_tmp, tmp[0], 0) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if (init_str(&env_tmp->env_vars[m].name, tmp[0]) != EXIT_SUCCESS \
		|| init_str(&env_tmp->env_vars[m].value, tmp[1]) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	env_tmp->env_vars[m + 1].name.str = NULL;
	env_tmp->env_vars[m + 1].value.str = NULL;	
	return (EXIT_SUCCESS);	
}

int	add_env_var(t_env *env, char *var)
{
	char	**tmp;
	t_env	env_tmp;

	(void)env;
	env_tmp = (t_env){0};
	env_tmp.env_vars_max = env->env_vars_max + 1;
	tmp = ft_split(var, '=');
	if (!tmp)
		return (-EXIT_FAILURE);
	if (find_and_update_env_var(env, tmp[0], tmp[1]) != -EXIT_FAILURE)
		return (EXIT_SUCCESS);
	ft_add(env, &env_tmp, var);    
	init_path(&env_tmp);
	init_cwd(&env_tmp);
	free_t_env(env);
	if (dup_tmp_to_env(env, &env_tmp, -1) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	free_t_env(&env_tmp);
	return (EXIT_SUCCESS);
}
