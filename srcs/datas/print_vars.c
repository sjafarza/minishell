/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/21 22:44:11 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_vars(t_env *env)
{
	int	i;

	// printf("Env variables max : %d\n", env->env_vars_max);
	i = 1;
	while (i < env->env_vars_max)
	{
		printf("%s=%s\n", env->env_vars[i].name.str, env->env_vars[i].value.str);
		i++;
	}
}
