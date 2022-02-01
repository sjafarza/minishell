/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 13:41:43 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	return_and_clean(t_line line_handler, t_str new_str, int new_i,
	int code)
{
	free((*line_handler.line));
	(*line_handler.line) = new_str.str;
	(*line_handler.i) = new_i;
	return (code);
}

int	replace_in_str_one_var(t_env *env, t_line line_handler, int end_var_name,
int size_after_max_i)
{
	int			new_i;
	t_str		new_str;
	t_env_var	*var;

	new_str.len = (*line_handler.i);
	new_i = (*line_handler.i);
	var = find_env_vars_t_str(env, (t_str){(*line_handler.line) + new_i + 1,
			end_var_name});
	if (var)
		new_str.len += var->value.len;
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
	printf("%d;%s;%d;%d;%d\n",new_i, (*line_handler.line), (*line_handler.i)
		, end_var_name + 1, size_after_max_i + 1);
	ft_memcpy(new_str.str + new_i, (*line_handler.line) + (*line_handler.i)
		+ end_var_name + 1, size_after_max_i + 1);
	return (return_and_clean(line_handler, new_str, new_i, EXIT_SUCCESS));
}
