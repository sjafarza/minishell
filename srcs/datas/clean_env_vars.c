/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/23 21:14:48 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_one_var(t_env_var	env_var)
{
	if (env_var.name.str)
		free(env_var.name.str);
	if (env_var.value.str)
		free(env_var.value.str);
	if (env_var.raw.str)
		free(env_var.raw.str);
}

void	clean_env_vars(t_env *env)
{
	clean_env_vars_array(&env->env_vars, env->env_vars_max);
}

void	clean_env_vars_array(t_env_var	**tmp_env_vars, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free_one_var((*tmp_env_vars)[i]);
		i++;
	}
	if (*tmp_env_vars)
		free(*tmp_env_vars);
	tmp_env_vars = NULL;
}
