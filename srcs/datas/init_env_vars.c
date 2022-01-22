/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_vars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 21:46:07 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define NO_ARRAY -1

#define STRING_NAME		0
#define STRING_VALUE	1
#define STRING_RAW		2
#define MAX_STRINGS		3

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

static int	get_array_size(char **arr)
{
	int i;

	i = 0;
	if (!arr)
		return NO_ARRAY;
	while (arr[i])
		i++;
	return (i);
}

static int	strings_clean(char *strings[MAX_STRINGS], int code)
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
	return (code);
}

int	init_env_vars(t_env *env, char **raw_env)
{
	int		i;
	int		separator_index;
	char	*strings[MAX_STRINGS];

	strings_init(strings);
	i = 0;
	env->raw_env = raw_env;
	env->env_vars_max = get_array_size(raw_env);
	if (env->env_vars_max == NO_ARRAY || env->env_vars_max == 0)
		return (-EXIT_FAILURE);
	env->env_vars_max++;
	env->env_vars = (t_env_var*)malloc(sizeof(t_env_var) * env->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);
	strings[STRING_NAME] = ft_strdup("?");
	strings[STRING_VALUE] = ft_strdup("0");
	env->exit_value = 0;
	env->env_vars[i] = (t_env_var){(t_str){0}, (t_str){0}, (t_str){0}};
	if (init_t_str(&env->env_vars[i].name, strings[STRING_NAME]) != EXIT_SUCCESS || init_t_str(&env->env_vars[i].value, strings[STRING_VALUE]) != EXIT_SUCCESS)
		return (strings_clean(strings, -EXIT_FAILURE));
	i++;
	while (i < env->env_vars_max)
	{
		separator_index = ft_strchr_index(raw_env[i - 1], '=');
		if(separator_index < 0)
			return (-EXIT_FAILURE);
		strings[STRING_RAW] = ft_strdup(raw_env[i - 1]);
		strings[STRING_NAME] = ft_substr(raw_env[i - 1], 0, separator_index);
		strings[STRING_VALUE] = ft_substr(raw_env[i - 1], separator_index + 1, ft_strlen(raw_env[i - 1]));
		if (init_t_str(&env->env_vars[i].name, strings[STRING_NAME]) != EXIT_SUCCESS
		|| init_t_str(&env->env_vars[i].value, strings[STRING_VALUE]) != EXIT_SUCCESS
		|| init_t_str(&env->env_vars[i].raw, strings[STRING_RAW]) != EXIT_SUCCESS)
			return (strings_clean(strings, -EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}
