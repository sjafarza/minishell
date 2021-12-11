/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:04:14 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 18:04:20 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		pwd_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	(void)env;
    printf("%s\n", env->cwd);
    return (EXIT_SUCCESS);
}

