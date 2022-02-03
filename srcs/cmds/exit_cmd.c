/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:55:54 by sjafarza          #+#    #+#             */
/*   Updated: 2022/02/03 10:52:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_value(char const *arg, int *result)
{
	int				tmp;
	char			*checker;
	unsigned int	checker_length;

	if (arg == NULL)
		return (-EXIT_FAILURE);
	tmp = ft_atoi(arg);
	checker = ft_itoa(tmp);
	checker_length = ft_strlen(checker);
	if (!(ft_strncmp(arg, checker, checker_length) == 0 && ft_strlen(arg)
			== checker_length))
	{
		free(checker);
		return (-EXIT_FAILURE);
	}
	free(checker);
	*result = tmp;
	return (EXIT_SUCCESS);
}

#define CMD_NAME	"exit"

int	exit_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	int	value;

	(void)cmd;
	value = 0;
	if (args[1])
	{
		if (parse_value(args[1], &value) != EXIT_SUCCESS)
		{
			if (silent == false)
				print_cmd_error(CMD_NAME, args[1],
					" : argument numérique nécessaire", NULL);
			env->exit_cmd_value = 2;
			return (EXIT_MINISHELL);
		}
	}
	if (array_len(args) > 2)
	{
		if (silent == false)
			print_cmd_error(CMD_NAME, "trop d'arguments", NULL, NULL);
		return (1);
	}
	env->exit_cmd_value = value;
	if (silent == false)
		printf("exit\n");
	return (EXIT_MINISHELL);
}
