/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:13:42 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 22:13:47 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		cd_cmd(t_env *env, const char *cmd, const char **args)
{
	(void)cmd;
	(void)args;
	(void)env;
    printf("\nI am in cd_cmd \n");
	return (EXIT_SUCCESS);
}
