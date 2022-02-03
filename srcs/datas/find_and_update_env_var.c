/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_update_env_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/02/03 09:47:55 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	if_path_then_update(t_env *env, char *name)
{
	if (ft_strncmp(name, PATH_STR, PATH_LEN + 1) == 0)
		return (init_path(env));
	return (EXIT_SUCCESS);
}

int	update_env_var(t_env_var *var, char *new_value)
{
	if (!var)
		return (-EXIT_FAILURE);
	if (var->value.str)
		free(var->value.str);
	return (init_t_str(&var->value, new_value));
}

int	find_and_update_env_var(t_env *env, char *var_name, char *new_value)
{
	if (update_env_var(find_env_vars(env, var_name), new_value) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	return (if_path_then_update(env, var_name));
}
