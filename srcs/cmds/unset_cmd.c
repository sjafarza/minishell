/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/25 14:43:22 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_as_env_var_name(const char *args)
{
	int	j;
	int	error;

	j = 0;
	error = false;
	while (args[j])
	{
		if (!ft_is_valid_for_env_var_name(args[j++]))
		{
			printf("minshell: unset:( %s ):\
					 not valid identifier\n", args);
			error = true;
			break ;
		}
	}
	return (error);
}

int	unset_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;
	int	r;

	(void)cmd;
	if (env->pipex_stack.total_item > 1)
		return (0);
	if (!args[1])
		return (1);
	i = 0;
	while (args[++i])
	{
		if (is_valid_as_env_var_name(args[i]))
			continue ;
		if ((ft_strlen(args[i]) == PATH_LEN) && \
			(ft_strncmp(args[i], PATH_STR, PATH_LEN) == 0))
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
	return (0);
}
