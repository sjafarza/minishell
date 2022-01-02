/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:47:48 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/04 09:55:36 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	echo_cmd(t_env *env, const char *cmd, const char **args)
{
	int		i;

	(void)cmd;
	(void)env;
	i = 1;
	if (args[1] && !ft_strncmp(args[1], "-n", 2) && ft_strlen(args[1]) == 2)
	{
		i++;
		while (args[i] && !ft_strncmp(args[i], "-n", 2) \
			&& ft_strlen(args[i]) == 2)
			i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (args[1] && !ft_strncmp(args[1], "-n", 2) && ft_strlen(args[1]) == 2)
		return (EXIT_SUCCESS);
	printf("\n");
	return (EXIT_SUCCESS);
}
