/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/27 15:28:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_as_env_var_name(const char *args)
{
	int	j;

	j = 0;
	while (args[j])
	{
		if (!ft_is_valid_for_env_var_name(args[j++]))
		{
			printf("minshell: unset:( %s ):\
					 not valid identifier\n", args);
			return (true);
		}
	}
	return (false);
}

int	unset_cmd(t_env *env, const char *cmd, const char **args)
{
}

int	unset_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;
	int	r;
	int	error;

	(void)cmd;
	error = false;
	if (env->pipex_stack.total_item > 1)
		return (0);
	if (!args[1])
		return (0);
	i = 0;
	while (args[++i])
	{
		if (is_valid_as_env_var_name(args[i]))
		{
			error = true;
			continue ;
		}
		if ((ft_strlen(args[i]) == PATH_LEN)
			&& (ft_strncmp(args[i], PATH_STR, PATH_LEN) == 0))
		{
			if (env->paths)
				free_array(env->paths);
			env->paths = ft_split("", ':');
			if (!env->paths)
				return (1);
		}
		r = del_env_var(env, (char *)args[i]);
		if (r != EXIT_SUCCESS)
			return (1);
	}
	return (error);
}
