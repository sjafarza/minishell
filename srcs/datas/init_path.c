/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:36:46 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_path(t_env *env)
{
	t_env_var	*var;

	var = get_or_init_and_get_env_var(env, PATH_STR);
	if (!var)
		return (-EXIT_FAILURE);
	if (env->paths)
		free_array(env->paths);
	env->paths = ft_split(var->value.str, ':');
	if (!env->paths)
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
