/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:47:48 by sjafarza          #+#    #+#             */
/*   Updated: 2022/02/03 11:06:42 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_only_n(const char *l)
{
	int	i;

	i = 0;
	while (l[i])
	{
		if (l[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	echo_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	int		i;
	int		is_n;

	(void)cmd;
	(void)env;
	if (silent == true)
		return (0);
	i = 0;
	is_n = false;
	while (args[++i] && !ft_strncmp(args[i], "-", 1)
		&& is_only_n(args[i] + 1) == true)
		is_n = true;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (is_n == true)
		return (0);
	printf("\n");
	return (0);
}
