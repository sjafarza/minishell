/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 21:04:40 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	print_vars(t_env *env)
{
	int	i;

	printf("Env variables max : %d\n", env->env_vars_max);
	i = 0;
	while (i < env->env_vars_max)
	{
		printf("NAME:[%s] VALUE:[%s]\n", env->env_vars[i].name.str, env->env_vars[i].value.str);
		i++;
	}
}
