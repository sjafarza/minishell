/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/02/03 09:41:25 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	if_question_mark_update(t_env *env, t_env_var *var)
{
	char	*str_exit_value;

	if (var->name.len == 1 && ft_strncmp(var->name.str, "?", 1) == 0
		&& atoi(var->value.str) != env->exit_value)
	{
		str_exit_value = ft_itoa(env->exit_value);
		if (!str_exit_value)
			return (-EXIT_FAILURE);
		if (var->value.str)
			free(var->value.str);
		init_t_str(&(var->value), str_exit_value);
	}
	return (EXIT_SUCCESS);
}

t_env_var	*find_env_vars_t_str(t_env *env, t_str var)
{
	int		i;

	i = 0;
	if (!var.str || var.len <= 0)
		return (NULL);
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == var.len && \
				ft_strncmp(env->env_vars[i].name.str, var.str, var.len) == 0)
		{
			if_question_mark_update(env, &(env->env_vars[i]));
			return (&env->env_vars[i]);
		}
		i++;
	}
	return (NULL);
}

t_env_var	*find_env_vars(t_env *env, char const*var_name)
{
	if (!var_name)
		return (NULL);
	return (find_env_vars_t_str(env, (t_str){(char *)var_name,
			ft_strlen(var_name)}));
}
