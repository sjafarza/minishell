/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_raw_env_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 22:51:50 by saray             #+#    #+#             */
/*   Updated: 2022/01/22 22:51:55 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    **get_raw_env_array(t_env *env)
{
    char   **array;
    int     i;

    if (!env->env_vars)
		return (NULL);    
   	array = (char **)malloc(sizeof(char *) * env->env_vars_max);
    if (!array) 
        return (NULL);   
    i = -1;
    while (++i < env->env_vars_max)
    {
      
       if (env->env_vars[i].raw.str == NULL)
        i++; 
       //printf("env->env_vars[%d].raw.str = %s\n", i, env->env_vars[i].raw.str); 
      array[i] = env->env_vars[i].raw.str; 
      //printf("array[%d] = %s\n", i, array[i]);
      env->env_vars[i].raw.str = NULL;
    } 
    array[i] = 0;
    return (array);
}
    /*if (var[i])->raw.str == NULL)
        i++;
    array[i] = var[j]->raw.str; []

    var[i]->raw.str = NULL;  */ 

