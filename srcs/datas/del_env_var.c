/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:14:02 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/07 13:22:44 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_str(t_str *obj, char *s)
{
	if (!obj || !s)
		return (-EXIT_FAILURE);
	obj->str = ft_strdup(s);
	obj->len = ft_strlen(s);
	return (EXIT_SUCCESS);
}

int	dup_tmp_to_env(t_env *env, t_env *tmp, int i)
{
	env->env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);	
	env->env_vars_max = tmp->env_vars_max;
	while (++i < env->env_vars_max)
		if (init_str(&env->env_vars[i].name, tmp->env_vars[i].name.str) \
			!= EXIT_SUCCESS || init_str(&env->env_vars[i].value, \
				tmp->env_vars[i].value.str) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
	//env->env_vars[i].name.str = NULL;
	//env->env_vars[i].value.str = NULL;
	if (init_path(env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH PATH\n");
	if (init_cwd(env) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH CWD\n");
	return (EXIT_SUCCESS);
}

int	fill_tmp(t_env *env, t_env *tmp, char *var_name, int i)
{
	int	j;

	j = 0;
	tmp->env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp->env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);	
	printf("var_name in fill_tmp = %s\n", var_name);	
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == (int)ft_strlen(var_name) && \
				!ft_strncmp(env->env_vars[i].name.str, \
				var_name, ft_strlen(var_name)))
			i++;
		else
		{
			printf("je suis in else\n");
			if (init_str(&tmp->env_vars[j].name, env->env_vars[i].name.str) \
				!= EXIT_SUCCESS || init_str(&tmp->env_vars[j].value, \
				env->env_vars[i].value.str) != EXIT_SUCCESS)
				{
					printf("fail\n");
					return (-EXIT_FAILURE);
				}
			printf("ttttmp->env_var[%d].ame = %s ,env-env_vars[%d].value.str = %s\n", j, tmp->env_vars[j].name.str, i , tmp->env_vars[i].value.str);
			j++;
			i++;
		}
	}
	//tmp->env_vars[j].name.str = NULL;
	//tmp->env_vars[j].value.str = NULL;
	printf("****chek unset in fill_tmp***\n");
	print_vars(tmp);
	return (EXIT_SUCCESS);
}

int	del_env_var(t_env *env, char *var_name)
{
	t_env	tmp;

	tmp = (t_env){0};
	if (!var_name)
		return (-EXIT_FAILURE);
	if(!find_env_vars(env, var_name))
		return (EXIT_SUCCESS);	
	tmp.env_vars_max = env->env_vars_max - 1;
	if (fill_tmp(env, &tmp, var_name, env->env_vars_max) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	init_path(&tmp);
	init_cwd(&tmp);
	free_t_env(env);
	env = NULL;
	if (dup_tmp_to_env(env, &tmp, -1) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	free_t_env(&tmp);
	return (EXIT_SUCCESS);
}
