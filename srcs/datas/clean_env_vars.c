/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 20:22:31 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	clean_env_vars(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->env_vars_max)
	{
		if(env->env_vars[i].name.str)
			free(env->env_vars[i].name.str);
		if(env->env_vars[i].value.str)
			free(env->env_vars[i].name.str);
		i++;
	}
	free(env->env_vars);
}
