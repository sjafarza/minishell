/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/17 09:37:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	select_right_cmd(t_env *env, const char *cmd)
{
	(void)env;
	int	i;
	int	len_cmd;

	if (!cmd)
		return (-EXIT_FAILURE);
	len_cmd = ft_strlen(cmd);
	i = MAX_CMD;
	while (--i > 0)
	{
		if (len_cmd == g_cmd_dictionary[i].code.len && ft_strncmp(g_cmd_dictionary[i].code.str, cmd,
				g_cmd_dictionary[i].code.len) == 0)
			return (i);
	
	}
	return (i);
}
