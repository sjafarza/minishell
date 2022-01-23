/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/23 18:58:50 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define MAX_COMPLETES_PATHS 3

const static t_str	g_path_completes[MAX_COMPLETES_PATHS] = {
	(t_str){"/", 1},
	(t_str){"./", 2},
	(t_str){"../", 3},
};

int	is_path_absolute_or_relative(const char *cmd)
{
	int	i;

	i = 0;
	while (i < MAX_COMPLETES_PATHS)
	{
		if (ft_strncmp(g_path_completes[i].str, cmd,
				g_path_completes[i].len) == 0)
			return (true);
		i++;
	}
	return (false);
}

char	*get_full_cmd_from_path_int(char *cmd_end_path, char **possibles_paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	while (possibles_paths[i])
	{
		if (cmd_path)
			free(cmd_path);
		cmd_path = ft_strjoin(possibles_paths[i], cmd_end_path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		i++;
	}
	if (cmd_path)
		free(cmd_path);
	return (NULL);
}

char	*get_full_cmd_from_path(t_env *env, const char *cmd_name)
{
	char	*cmd_path;
	char	*cmd_end_path;

	cmd_end_path = ft_strjoin("/", cmd_name);
	if (!cmd_end_path)
		return (NULL);
	cmd_path = get_full_cmd_from_path_int(cmd_end_path, env->paths);
	free(cmd_end_path);
	return (cmd_path);
}

char	*get_full_cmd(t_env *env, const char *cmd)
{
	if (is_path_absolute_or_relative(cmd) && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (!env->paths)
		return (NULL);
	return (get_full_cmd_from_path(env, cmd));
}

#define COMMAND_NOT_FOUND_MSG "Command not found: %s\n"
#define COMMAND_NOT_FOUND_CODE 1
#define EXEC_ERROR_CODE 127

int	bash_cmd(t_env *env, const char *cmd, const char **args)
{
	char	*full_cmd;
	int		ret;
	char	**raw_env;

	(void)args;
	full_cmd = get_full_cmd(env, cmd);
	if (!full_cmd)
	{
		printf(COMMAND_NOT_FOUND_MSG, cmd);
		return (COMMAND_NOT_FOUND_CODE);
	}
	printf("FULL_CMD : %s\n", full_cmd);
	raw_env = get_raw_env_array(env);
	ret = execve(full_cmd, (char *const *)args, raw_env);
	free(full_cmd);
	free_array(raw_env);
	// close(env->pipes_handles[id]);
	if (ret < 0)
		return (EXEC_ERROR_CODE); 
	return (ret);
}
