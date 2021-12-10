/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/04 09:24:45 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	select_right_cmd(t_env *env, const char *cmd, const char** args)
{
	(void)env;
	int	i;
	int	len_cmd;

	if (!cmd)
	{
		printf("I am in the bash_cmd with word = null \n");
		return (g_cmd_dictionary[0].fun(env, cmd, args));
	}
	len_cmd = ft_strlen(cmd);
	i = MAX_CMD;
	while (--i > 0)
	{
		if (len_cmd == g_cmd_dictionary[i].code.len && ft_strncmp(g_cmd_dictionary[i].code.str, cmd,
				g_cmd_dictionary[i].code.len) == 0)
		{
			printf("i = %d\n", i);
			return (g_cmd_dictionary[i].fun(env, cmd, args));
		}
	
	}
	printf("I am in the bash_cmd = %d\n", i);
	return (g_cmd_dictionary[0].fun(env, cmd, args));
}
