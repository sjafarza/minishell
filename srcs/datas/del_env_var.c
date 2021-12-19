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
	if (!obj /*|| !s*/)
		return (-EXIT_FAILURE);
	if (!s)
		s = " ";	
	obj->str = ft_strdup(s);
	obj->len = ft_strlen(s);
	return (EXIT_SUCCESS);
}

/*int	dup_tmp_to_env(t_env *env, t_env *tmp, int i)
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
}*/

int	fill_tmp(t_env *env, t_env_var *tmp, char *var_name, int max)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	max = max + 1 -1;
	printf("var_name in fill_tmp = %s\n", var_name);	
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == (int)ft_strlen(var_name) && \
				!ft_strncmp(env->env_vars[i].name.str, \
				var_name, ft_strlen(var_name)))
			i++;
		else
		{
			if (init_str(&tmp[j].name, env->env_vars[i].name.str) \
				!= EXIT_SUCCESS || init_str(&tmp[j].value, \
				env->env_vars[i].value.str) != EXIT_SUCCESS)
				{
					printf("fail\n");
					return (-EXIT_FAILURE);
				}
			j++;
			i++;
		}
	}
	printf("ok\n");
	tmp[j].name.str = "";
	tmp[j].value.str = "";
	return (EXIT_SUCCESS);
}

int	del_env_var(t_env *env, char *var_name)
{
	t_env_var	*tmp_env_vars;
	int			tmp_env_vars_max;

	//printf("**args[i] = var_name = %s\n", var_name);
	if (!var_name)
		return (-EXIT_FAILURE);
	if(!find_env_vars(env, var_name))
		return (EXIT_SUCCESS);
	tmp_env_vars_max = env->env_vars_max - 1;		
	tmp_env_vars = (t_env_var *)malloc(sizeof(t_env_var) * tmp_env_vars_max);
	if (!env->env_vars)
		return (-EXIT_FAILURE);
	if (fill_tmp(env, tmp_env_vars, var_name, tmp_env_vars_max) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);	
	free(env->env_vars);
	env->env_vars = tmp_env_vars;
	env->env_vars_max -= 1;
	return (EXIT_SUCCESS);
}
