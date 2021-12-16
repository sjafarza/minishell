/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:13:42 by saray             #+#    #+#             */
/*   Updated: 2021/12/16 19:27:56 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		cd_cmd(t_env *env, const char *cmd, const char **args)
{
	int	args_len;
	t_env_var	*var;
	(void)cmd;
	(void)args;
	(void)env;

	args_len = array_len(args);
	printf("\nI am in cd_cmd %d\n", args_len);
	if (args_len > 2)
	{
		printf("%s: cd: trop d'arguments\n", PROMPT_STR);
		return (EXIT_SUCCESS);
	}
	if (env->pipex_stack.total_item > 1)
		return (EXIT_SUCCESS);
	if (args_len == 1)
	{
		var = find_env_vars(env, "HOME");
		if (!var)
			return (-EXIT_FAILURE);
		if (chdir(var->value.str) == -EXIT_FAILURE)
		{
			printf("%s: cd: %s: Aucun fichier ou dossier de ce type\n", PROMPT_STR, var->value.str);
			return (EXIT_SUCCESS);
		}
	}
	else
	{
		if (chdir(args[1]) == -EXIT_FAILURE)
		{
			printf("%s: cd: %s: Aucun fichier ou dossier de ce type\n", PROMPT_STR, args[1]);
			return (EXIT_SUCCESS);
		}
	}
	if (init_cwd(env) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
