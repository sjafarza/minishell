/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/29 10:26:42 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*find_env_vars_t_str(t_env *env, t_str var)
{
	int	i;

	i = 0;
	if (!var.str || var.len <= 0)
		return (NULL);
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == var.len && \
				ft_strncmp(env->env_vars[i].name.str, var.str, var.len) == 0)
			return (&env->env_vars[i]);
		i++;
	}
	return (NULL);
}

t_env_var	*find_env_vars(t_env *env, char *var_name)
{
	if (!var_name)
		return (NULL);
	return (find_env_vars_t_str(env, (t_str){var_name, ft_strlen(var_name)}));
}
