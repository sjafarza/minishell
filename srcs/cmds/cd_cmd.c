/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:13:42 by saray             #+#    #+#             */
/*   Updated: 2022/01/27 17:38:55 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define CD_ERROR_NO_FOLDER_OR_FILE_FMT	"%s: cd: %s: Aucun fichier ou dossier\
 de ce type\n"

int	go_to(const char *target_folder)
{	
	if (chdir(target_folder) == -EXIT_FAILURE)
	{
		printf(CD_ERROR_NO_FOLDER_OR_FILE_FMT, PROMPT_STR, target_folder);
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	go_back_to_var(t_env *env, const char *var_name_target_folder)
{
	t_env_var	*var;

	var = find_env_vars(env, (char *)var_name_target_folder);
	if (!var)
	{
		printf("%s: cd: << %s >> non défini\n", PROMPT_STR,
			var_name_target_folder);
		return (-EXIT_FAILURE);
	}
	return (go_to(var->value.str));
}

static int	cd_cmd_leave_early(t_env *env, int args_len, const char *cmd)
{
	(void)cmd;
	if (env->pipex_stack.total_item > 1)
		return (EXIT_SUCCESS);
	if (args_len > 2)
	{
		printf("%s: cd: trop d'arguments\n", PROMPT_STR);
		return (1);
	}
	if (env->pipex_stack.total_item > 1)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	cd_cmd(t_env *env, const char *cmd, const char **args)
{
	int			args_len;

	args_len = array_len(args);
	if (cd_cmd_leave_early(env, args_len, cmd) != EXIT_SUCCESS)
		return (1);
	if (args_len == 1)
	{
		if (go_back_to_var(env, HOME_STR) == -EXIT_FAILURE)
			return (1);
	}
	else
	{
		if (ft_strncmp(args[1], "-", 2) == 0)
		{
			if (go_back_to_var(env, OLDPWD_STR) == -EXIT_FAILURE)
				return (1);
		}
		else if (ft_strlen(args[1]) == 0)
			return (0);
		else if (go_to(args[1]) == -EXIT_FAILURE)
			return (1);
	}
	if (init_cwd(env) != EXIT_SUCCESS)
		return (1);
	return (0);
}
