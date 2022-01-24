/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:04:14 by saray             #+#    #+#             */
/*   Updated: 2022/01/21 15:55:44 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pwd_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	(void)env;
	printf("%s\n", env->cwd);
	//return (EXIT_SUCCESS);
	return (0);
}
