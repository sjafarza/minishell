/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/28 14:33:44 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_path(t_env *env)
{
	t_env_var	*var;

	var = find_env_vars_t_str(env, (t_str){PATH_STR, PATH_LEN});
	if (!var)
		return (-EXIT_FAILURE);
	env->paths = ft_split(var->value.str, ':');
	if (!env->paths)
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
