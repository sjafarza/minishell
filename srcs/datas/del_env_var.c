/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 10:14:02 by sjafarza          #+#    #+#             */
/*   Updated: 2021/12/06 10:14:15 by sjafarza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_str(t_str *obj, char* s)
{
	if (!obj || !s)
		return (-EXIT_FAILURE);
	obj->str = ft_strdup(s);;
	obj->len = ft_strlen(s);
	return (EXIT_SUCCESS);
}

int  del_env_var(t_env   *env, char  *var_name)
{
    int     i;
    int     j;
    t_env	tmp;

    //(void)env;
    //(void)var_name;
    tmp = (t_env){0};
    if (!var_name)
		return (-EXIT_FAILURE);
    tmp.env_vars_max = env->env_vars_max - 1;
    tmp.env_vars = (t_env_var*)malloc(sizeof(t_env_var) * tmp.env_vars_max);
    if (!env->env_vars)
		return (-EXIT_FAILURE);
    i = 0;
    j = 0;
	while (i < env->env_vars_max)
	{
		if (env->env_vars[i].name.len == (int)ft_strlen(var_name) &&
				!ft_strncmp(env->env_vars[i].name.str, var_name, ft_strlen(var_name)))
                i++;
        else
        {
            if (init_str(&tmp.env_vars[j].name, env->env_vars[i].name.str) != EXIT_SUCCESS \
                || init_str(&tmp.env_vars[j].value, env->env_vars[i].value.str) != EXIT_SUCCESS)
		        return (-EXIT_FAILURE);
            
                i++;
                j++;
        }
	}
    tmp.env_vars[j].name.str =  NULL;
    tmp.env_vars[j].value.str = NULL;
    init_path(&tmp);
    init_cwd(&tmp);
    //clean_env_vars(env);
    free_t_env(env);
    //return(&tmp)
    env = &tmp;
    //printf("Print test for new list of t_env env\n");
    //print_vars(env);
	return (EXIT_SUCCESS);
}
