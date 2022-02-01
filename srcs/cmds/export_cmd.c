/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 20:48:31 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define STRING_NAME		0
#define STRING_VALUE	1
#define STRING_RAW		2
#define MAX_STRINGS		3

#define ARG				0
#define MSG				1
#define CONST_MAX		2

#define CMD_NAME	"export"

static int	strings_clean(char *strings[MAX_STRINGS], int code,
	const char *str[CONST_MAX], int silent)
{
	int	i;

	i = 0;
	while (i < MAX_STRINGS)
	{
		if (strings[i])
			free(strings[i]);
		strings[i] = NULL;
		i++;
	}
	if (silent == false && str && str[MSG] && str[ARG])
		print_cmd_error(CMD_NAME, str[ARG], " -> ", str[MSG]);
	return (code);
}

static int	prepare_var_elements(t_env *env, const char *arg,
	char *strings[MAX_STRINGS], int silent)
{
	int	k;

	if (produce_name_value((char *)arg, &strings[STRING_NAME],
			&strings[STRING_VALUE]) == -EXIT_FAILURE)
		return (strings_clean(strings, -EXIT_FAILURE, (const char *[CONST_MAX]){
				arg, "not valid identifier"}, silent));
	if (ft_strlen(strings[STRING_NAME]) <= 0)
		return (strings_clean(strings, -EXIT_FAILURE, (const char *[CONST_MAX]){
				arg, "var name must contain at least 1 character"}, silent));
	k = -1;
	while (strings[STRING_NAME][++k])
		if (ft_is_valid_for_env_var_name(strings[STRING_NAME][k]) == 0)
			return (strings_clean(strings, -EXIT_FAILURE,
					(const char *[CONST_MAX]){arg,
					"not valid identifier"}, silent));
	if (!strings[STRING_VALUE])
		return (strings_clean(strings, EXIT_SUCCESS, NULL, silent));
	strings[STRING_RAW] = ft_strdup(arg);
	if (!strings[STRING_RAW])
		return (strings_clean(strings, -EXIT_FAILURE, NULL, silent));
	if ((ft_strlen(strings[STRING_NAME]) == PATH_LEN)
		&& (ft_strncmp(strings[STRING_NAME], PATH_STR, PATH_LEN) == 0)
		&& init_path(env) == -EXIT_FAILURE)
		return (strings_clean(strings, -EXIT_FAILURE, NULL, silent));
	return (EXIT_SUCCESS);
}

int	export_cmd(t_env *env, const char *cmd, const char **args, int silent)
{
	int		i;
	char	*strings[MAX_STRINGS];

	(void)cmd;
	i = 0;
	ft_memset(strings, (int) NULL, sizeof(char *) * MAX_STRINGS);
	while (args[++i])
	{
		if (prepare_var_elements(env, args[i], strings, silent)
			!= EXIT_SUCCESS)
			return (1);
		if (!strings[STRING_NAME])
			continue ;
		if (find_and_update_env_var(env, strings[STRING_NAME],
				strings[STRING_VALUE]) == EXIT_SUCCESS)
		{
			free(strings[STRING_NAME]);
			free(strings[STRING_RAW]);
		}
		else if (add_new_env_by_value_name_raw(env, strings[STRING_NAME],
				strings[STRING_VALUE], strings[STRING_RAW]) == -EXIT_FAILURE)
			return (strings_clean(strings, 1, NULL, silent));
	}
	return (EXIT_SUCCESS);
}
