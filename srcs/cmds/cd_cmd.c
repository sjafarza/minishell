/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 22:13:42 by saray             #+#    #+#             */
/*   Updated: 2022/02/03 09:54:12 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define CMD_NAME	"cd"

int	go_to(const char *target_folder, int silent)
{	
	if (chdir(target_folder) == -EXIT_FAILURE)
	{
		if (silent == false)
			print_cmd_error(CMD_NAME, target_folder,
				": Aucun fichier ou dossier", NULL);
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	go_back_to_var(t_env *env, const char *var_name_target_folder, int silent)
{
	t_env_var	*var;

	var = find_env_vars(env, (char *)var_name_target_folder);
	if (!var)
	{
		if (silent == false)
			print_cmd_error(CMD_NAME, "<< ", var_name_target_folder,
				" >> non défini");
		return (-EXIT_FAILURE);
	}
	return (go_to(var->value.str, silent));
}

static int	cd_cmd_leave_early(t_env *env, int args_len, const char *cmd,
	int silent)
{
	(void)cmd;
	if (args_len > 2)
	{
		if (silent == false)
			print_cmd_error(CMD_NAME, "trop d'arguments", NULL, NULL);
		return (1);
	}
	if (env->pipex_stack.total_item > 1)
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	cd_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	int			args_len;

	args_len = array_len(args);
	if (cd_cmd_leave_early(env, args_len, cmd, silent) != EXIT_SUCCESS)
		return (1);
	if (args_len == 1)
	{
		if (go_back_to_var(env, HOME_STR, silent) == -EXIT_FAILURE)
			return (1);
	}
	else
	{
		if (ft_strncmp(args[1], "-", 2) == 0)
		{
			if (go_back_to_var(env, OLDPWD_STR, silent) == -EXIT_FAILURE)
				return (1);
		}
		else if (ft_strlen(args[1]) == 0)
			return (0);
		else if (go_to(args[1], silent) == -EXIT_FAILURE)
			return (1);
	}
	if (init_cwd(env) != EXIT_SUCCESS)
		return (1);
	return (0);
}
