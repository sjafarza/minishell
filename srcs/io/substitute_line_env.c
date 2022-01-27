/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_line_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 21:48:45 by saray             #+#    #+#             */
/*   Updated: 2022/01/26 21:48:50 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define REPLACED 0
#define NOT_REPLACED -22

int substitute_line_env(t_env *env, char *line)
{
    int	end_var_name_abs;
	int	res;
    int i;

	i = 0;
	printf("1\n");
    end_var_name_abs = go_to_next_needed_i(line,
			&ft_is_valid_for_env_var_name, i + 1);
    printf("2\n");
	printf("env_var_name_abs = %d\n", end_var_name_abs);        
	if (end_var_name_abs == i + 1
		&& (line)[end_var_name_abs] == '?')
		end_var_name_abs++;
    printf("3\n");    
	if (end_var_name_abs == (i + 1))
		return (NOT_REPLACED);
    printf("4\n");
	printf("1 line = %s\n", line);
	res = replace_in_str_one_var(env,
			(t_line){&line, &i},
			end_var_name_abs - (i - 1),
			ft_strlen(/*end_var_name_abs + */line));
    printf("res = %d\n", res); 
	printf("line = %s\n", line);       
	if (res != EXIT_SUCCESS)
		return (res);
	printf("yes\n");	
	return (REPLACED);
}
