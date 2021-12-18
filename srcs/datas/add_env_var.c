/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 09:59:06 by saray             #+#    #+#             */
/*   Updated: 2021/12/11 00:37:55 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_add(t_env *env, t_env *env_tmp, char	*var) 
{
	char	**tmp;
	int		m;

	tmp = ft_split(var, '=');
	if (!tmp)
		return (-EXIT_FAILURE);
	if (tmp[1] == NULL)
		tmp[1] = " ";	
	env_tmp->env_vars_max = env->env_vars_max + 1;
	m = env_tmp->env_vars_max - 1;
	if (fill_tmp(env, env_tmp, tmp[0], 0) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	printf("ok after fill\n");	
	if (init_str(&env_tmp->env_vars[m].name, tmp[0]) != EXIT_SUCCESS \
		|| init_str(&env_tmp->env_vars[m].value, tmp[1]) != EXIT_SUCCESS)
		return (-EXIT_FAILURE);
	printf("env_tmp->env_vars[%d].name.str = %s\n", m, env_tmp->env_vars[m].name.str);	
	//env_tmp->env_vars[m + 1].name.str = NULL;
	//env_tmp->env_vars[m + 1].value.str = NULL;	
	return (EXIT_SUCCESS);	
}

int	add_env_var(t_env *env, char *var)
{
	char	**tmp;
	t_env	env_tmp;

	(void)env;
	env_tmp = (t_env){0};
	//env_tmp.env_vars_max = env->env_vars_max + 1;
	tmp = ft_split(var, '=');
	if (!tmp)
		return (-EXIT_FAILURE);
	printf("tmp[0] = %s\n", tmp[0]);
	printf("tmp[1] = %s\n", tmp[1]);	
	if (find_and_update_env_var(env, tmp[0], tmp[1]) != -EXIT_FAILURE)
		return (EXIT_SUCCESS);
	printf("not find in list \n");	
	ft_add(env, &env_tmp, var);
	printf("ok after ft_add\n");    
	if (init_path(&env_tmp) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH PATH\n");
	printf("1\n");
	if (init_cwd(&env_tmp) != EXIT_SUCCESS)
		printf("AN ERROR OCCURED WITH CWD\n");
	printf("2\n");
	free_t_env(env);
	printf("3\n");
	if (dup_tmp_to_env(env, &env_tmp, -1) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	printf("4\n");
	free_t_env(&env_tmp);
	printf("5\n");
	return (EXIT_SUCCESS);
}
