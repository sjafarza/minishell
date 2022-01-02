/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_and_update_env_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/16 22:30:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	find_and_update_env_var(t_env *env, char *var_name, char *new_value)
{
	t_env_var	*var;

	var = find_env_vars(env, var_name);
	if (!var)
		return (-EXIT_FAILURE);
	if (var->value.str)
		free(var->value.str);
	return (init_t_str(&var->value, new_value));
}
