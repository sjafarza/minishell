/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_empty_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/23 21:13:15 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env_var	*init_empty_env_var(t_env *env, char const *name, char const *value)
{
	char	*final_name;
	char	*final_value;

	final_name = ft_strdup(name);
	final_value = ft_strdup(value);
	if (add_new_env_by_value_name_raw(env, final_name, \
		final_value, NULL) == EXIT_SUCCESS)
		return (find_env_vars(env, (char *)name));
	if (final_name)
		free(final_name);
	if (final_value)
		free(final_value);
	return (NULL);
}

t_env_var	*get_or_init_and_get_env_var(t_env *env, char const *name)
{
	t_env_var	*var;

	var = find_env_vars(env, name);
	if (!var)
		var = init_empty_env_var(env, name, "");
	return (var);
}
