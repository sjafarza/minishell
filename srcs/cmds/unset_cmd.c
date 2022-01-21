/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 16:12:52 by sjafarza          #+#    #+#             */
/*   Updated: 2022/01/21 22:35:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_cmd(t_env *env, const char *cmd, const char **args)
{
	int	i;
	int	j;
	int	r;
	int	error;

	(void)cmd;
	if (!args[1])
		return (-EXIT_FAILURE);
	i = 0;
	while (args[++i])
	{
		j = 0;
		error = false;
		while (args[i][j])
		{
			if (!ft_is_valid_for_env_var_name(args[i][j++]))
			{
				printf("minshell: unset:( %s ): not valid identifier\n", args[i]);
				error = true;
				break;
			}
		}
		if (error)
			continue;
		if ((ft_strlen(args[i]) == PATH_LEN) && (ft_strncmp(args[i], PATH_STR, PATH_LEN) == 0))
		{
			if (env->paths)
				free_array(env->paths);
			env->paths = ft_split("", ':');
			if (!env->paths)
				return (-EXIT_FAILURE);
		}
		r = del_env_var(env, (char *)args[i]);
		if (!r)
			return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
