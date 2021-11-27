/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 19:13:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

int	select_right_cmd(t_env *env, const char *cmd, const char** args)
{
	(void)env;
	int	i;

	i = MAX_CMD;
	while (--i >= 0)
	{
		if (ft_strncmp(g_cmd_dictionary[i].code.str, cmd,
				g_cmd_dictionary[i].code.len) == 0)
		{
			return (g_cmd_dictionary[i].fun(cmd, args));
		}
	}
	return (EXIT_FAILURE);
}
