/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:04:14 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 15:37:58 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	(void)cmd;
	(void)args;
	(void)env;
	if (silent == true)
		return (0);
	printf("%s\n", env->cwd);
	return (0);
}
