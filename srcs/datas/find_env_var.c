/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 22:08:04 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_env_var	*find_env_vars_t_str(t_env *env, t_str var)
{
	int	i;

	i = 0;
	while (i < env->env_vars_max)
	{
		if(env->env_vars[i].name.len == var.len)
			if(env->env_vars[i].name.len == var.len)
		if (ft_strncmp(env->env_vars[i].name.str, var.str, var.len) == 0)
			return (&env->env_vars[i]);
		i++;
	}
	return (NULL);
}

t_env_var	*find_env_vars(t_env *env, char* var_name)
{
	return (find_env_vars_t_str(env, (t_str){var_name, ft_strlen(var_name)}));
}
