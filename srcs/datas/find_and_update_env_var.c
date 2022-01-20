/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_update_env_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/20 15:32:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	return (update_env_var(find_env_vars(env, var_name), new_value));
}
