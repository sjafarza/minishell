/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/02/01 15:23:05 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	(void)cmd;
	(void)args;
	if (silent == true)
		return (0);
	print_vars(env);
	return (0);
}
