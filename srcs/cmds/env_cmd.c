/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 15:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/25 14:41:48 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	(void)env;
	print_vars(env);
	return (0);
}
