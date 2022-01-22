/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:13:46 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 21:24:40 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define STRING_NAME		0
#define STRING_VALUE	1
#define STRING_RAW		2
#define MAX_STRINGS		3

static int	strings_clean(char *strings[MAX_STRINGS], int code, const char *arg, const char *message)
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
	if (message && arg)
		printf("2minshell:export:(%s): %s\n", arg, message);
	return (code);
}

static void	strings_init(char *strings[MAX_STRINGS])
{
	int	i;

	i = 0;
	while (i < MAX_STRINGS)
	{
		strings[i] = NULL;
		i++;
	}
}

int	export_cmd(t_env *env, const char *cmd, const char **args)
{
	int		i;
	int		k;
	char	*strings[MAX_STRINGS];

	
	(void)cmd;
	i = 0;
	k = -1;
	strings_init(strings);
	while (args[++i])
	{
		if (produce_name_value((char *)args[i], &strings[STRING_NAME], &strings[STRING_VALUE]) == -EXIT_FAILURE)
			return (strings_clean(strings, -EXIT_FAILURE, args[i], "not valid identifier"));
		if (ft_strlen(strings[STRING_NAME]) <= 0)
			return (strings_clean(strings, -EXIT_FAILURE, args[i], "var name must contain at least 1 character"));
		while (strings[STRING_NAME][++k])
			if (ft_is_valid_for_env_var_name(strings[STRING_NAME][k]) == 0)
				return (strings_clean(strings, -EXIT_FAILURE, args[i], "not valid identifier"));
		strings[STRING_RAW] = ft_strdup(args[i]);
		if (!strings[STRING_RAW])
			return (strings_clean(strings, -EXIT_FAILURE, NULL, NULL));
		if ((ft_strlen(strings[STRING_NAME]) == PATH_LEN) && (ft_strncmp(strings[STRING_NAME], PATH_STR, PATH_LEN) == 0) && init_path(env) == -EXIT_FAILURE)
			return (strings_clean(strings, -EXIT_FAILURE, NULL, NULL));
		if (find_and_update_env_var(env, strings[STRING_NAME], strings[STRING_VALUE]) == EXIT_SUCCESS)
		{
			free(strings[STRING_NAME]);
			free(strings[STRING_RAW]);
		}
		else if (add_new_env_by_value_name_raw(env, strings[STRING_NAME], strings[STRING_VALUE], strings[STRING_RAW]) == -EXIT_FAILURE)
			return (strings_clean(strings, -EXIT_FAILURE, NULL, NULL));
	}
	return (EXIT_SUCCESS);
}
