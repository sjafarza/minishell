/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/23 18:05:26 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	select_right_cmd(const char *cmd, const char **args)
{
	int	i;
	int	len_cmd;

	signal(SIGQUIT, ft_sig_ctr_backslash2);
	signal(SIGINT, ft_sig_ctr_c);
	if (!cmd)
		return (-EXIT_FAILURE);
	len_cmd = ft_strlen(cmd);
	i = MAX_CMD;
	while (--i > 0)
	{
		if ((len_cmd == g_cmd_dictionary[i].code.len
				&& ft_strncmp(g_cmd_dictionary[i].code.str, cmd,
					g_cmd_dictionary[i].code.len) == 0)
			&& (g_cmd_dictionary[i].max_args_len == ANY_SIZE
				|| g_cmd_dictionary[i].max_args_len >= array_len(args)))
			return (i);
	}
	return (i);
}
