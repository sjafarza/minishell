/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/28 11:37:25 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	return_and_clean(t_line line_handler, t_str new_str, int new_i,
	int code)
{
	//printf("ret and clean, new_str.str = %s\n", new_str.str);
	free((*line_handler.line));
	(*line_handler.line) = new_str.str;
	(*line_handler.i) = new_i;
	//printf("ret and clean, line = %s\n", (*line_handler.line));
	return (code);
}

int	replace_in_io(t_env *env, t_line line_handler, int end_var_name,
int size_after_max_i)
{
	int			new_i;
	t_str		new_str;
	t_env_var	*var;

	printf(" i in replace = %d\n", (*line_handler.i));
	new_str.len = (*line_handler.i);
	new_i = (*line_handler.i);
	//printf("ft_strlen(*line_handler.line) = %lu\n",ft_strlen(*line_handler.line));
	//printf("end_var_name = %d\n", end_var_name);
	printf("i serch = %s with len of %lu\n",(*line_handler.line) + new_i + 1, (ft_strlen(*line_handler.line)) - (*line_handler.i)- 1);
	var = find_env_vars_t_str(env, (t_str){(*line_handler.line) + new_i + 1,
			/*end_var_name */ (ft_strlen(*line_handler.line)) -(*line_handler.i) - 1});
	printf("len of var finded = %d\n", var->value.len);		
	if (var)
		new_str.len += var->value.len;
	printf("len for malloc = %d\n", new_str.len);	
	new_str.len += size_after_max_i + 1;
	new_str.str = malloc(sizeof(char) * new_str.len);
	if (!new_str.str)
		return (-EXIT_FAILURE);
	ft_memcpy(new_str.str, (*line_handler.line), (*line_handler.i));
	if (var)
	{
		new_i += var->value.len;
		ft_memcpy(new_str.str + (*line_handler.i), var->value.str,
			var->value.len);
	}
	printf("*** len meme  = %d\n", size_after_max_i + 1);
	
	int t = ft_strlen(*line_handler.line) - (((ft_strlen(*line_handler.line)) -(*line_handler.i)) + (*line_handler.i));
	printf("t = %d\n", t);
	//printf("chek chel = %lu\n", ((ft_strlen(*line_handler.line)) -(*line_handler.i)) + (*line_handler.i));
	ft_memcpy(new_str.str + new_i, (*line_handler.line) + (*line_handler.i)
		+ end_var_name + 1, /*size_after_max_i + 1*/t);
	printf("chek print in replace , line= %s\n", new_str.str);	
	return (return_and_clean(line_handler, new_str, new_i, EXIT_SUCCESS));
}
