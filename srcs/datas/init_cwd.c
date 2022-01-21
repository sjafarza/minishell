/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/21 16:05:15 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static	int add_new_env_by_value_name_check(t_env *env, char *name, char *value)
{
	if (!name | !value)
		return (-EXIT_FAILURE);
	return (add_new_env_by_value_name(env, name, value));
}

t_env_var *init_empty_env_var(t_env *env, char const *name, char const *value)
{
	char	*final_name;
	char	*final_value;

	final_name = ft_strdup(name);
	final_value = ft_strdup(value);
	if (add_new_env_by_value_name_check(env, final_name, final_value) == EXIT_SUCCESS)
		return (find_env_vars(env, (char *)name));
	if (final_name)
		free(final_name);
	if (final_value)
		free(final_value);
	return (NULL);
}

int	init_cwd(t_env *env)
{
	t_env_var *pwd_var;
	t_env_var *oldpwd_var;

	if (env->cwd)
		free(env->cwd);
	env->cwd = getcwd(NULL, 0);
	pwd_var = find_env_vars(env, PWD_STR);
	oldpwd_var = find_env_vars(env, OLDPWD_STR);
	if (!pwd_var)
		pwd_var = init_empty_env_var(env, PWD_STR, "");
	if (!pwd_var)
		return (-EXIT_FAILURE);
	if (!oldpwd_var)
		oldpwd_var = init_empty_env_var(env, OLDPWD_STR, "");
	if (!oldpwd_var)
		return (-EXIT_FAILURE);
	if (update_env_var(oldpwd_var, pwd_var->value.str) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	pwd_var->value.str = NULL;
	if (!env->cwd | (update_env_var(pwd_var, ft_strdup(env->cwd)) != EXIT_SUCCESS))
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
