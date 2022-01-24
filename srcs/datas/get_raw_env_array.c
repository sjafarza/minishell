/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_env_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:51:50 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:32:24 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_raw_env_array(t_env *env)
{
	char	**array;
	int		i;
	int		j;

	if (!env->env_vars)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (env->env_vars_max + 1));
	if (!array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].raw.str == NULL)
		{
			i++;
			continue ;
		}
		array[j] = env->env_vars[i].raw.str;
		env->env_vars[i].raw.str = NULL;
		j++;
		i++;
	}
	array[j] = NULL;
	return (array);
}
