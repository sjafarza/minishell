/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 14:44:56 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_cwd(t_env *env)
{
	t_env_var *pwd_var;
	t_env_var *oldpwd_var;

	if (env->cwd)
		free(env->cwd);
	env->cwd = getcwd(NULL, 0);
	pwd_var = get_or_init_and_get_env_var(env, PWD_STR);
	oldpwd_var = get_or_init_and_get_env_var(env, OLDPWD_STR);
	pwd_var = get_or_init_and_get_env_var(env, PWD_STR);
	if (!pwd_var)
		return (-EXIT_FAILURE);
	if (!oldpwd_var)
		return (-EXIT_FAILURE);
	if (update_env_var(oldpwd_var, pwd_var->value.str) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	pwd_var->value.str = NULL;
	if (!env->cwd | (update_env_var(pwd_var, ft_strdup(env->cwd)) != EXIT_SUCCESS))
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
