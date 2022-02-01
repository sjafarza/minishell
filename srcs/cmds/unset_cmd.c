/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/02/01 20:58:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define CMD_NAME	"unset"

static int	is_valid_as_env_var_name(char *arg, int silent)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (!ft_is_valid_for_env_var_name(arg[j++]))
		{
			if (silent != true)
				print_cmd_error(CMD_NAME, "(", arg, "): not valid identifier");
			return (true);
		}
	}
	return (false);
}

int	update_path_if_needed(t_env *env, int i, const char **args)
{
	if (ft_strncmp(args[i], PATH_STR, PATH_LEN + 1) == 0)
	{
		if (env->paths)
			free_array(env->paths);
		env->paths = ft_split("", ':');
		if (!env->paths)
			return (1);
	}
	return (EXIT_SUCCESS);
}

int	unset_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	int	i;
	int	error;

	(void)cmd;
	error = false;
	if (!args[1])
		return (0);
	i = 0;
	while (args[++i])
	{
		if (is_valid_as_env_var_name((char *)args[i], silent))
		{
			error = true;
			continue ;
		}
		if (update_path_if_needed(env, i, args) != EXIT_SUCCESS)
			return (1);
		if (del_env_var(env, (char *)args[i]) != EXIT_SUCCESS)
			return (1);
	}
	return (error);
}
