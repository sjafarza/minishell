/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/21 09:36:57 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	replace_in_str_one_var(t_env *env, t_line line_handler, int *max_i,
int size_after_max_i)
{
	int			new_i;
	int			len_right;
	int			end_var_name;
	t_str		new_str;
	t_env_var	*var;

	new_str.len = (*line_handler.i);
	new_i = (*line_handler.i);
	end_var_name = (*max_i) - (*line_handler.i) - 1;
	var = find_env_vars_t_str(env, (t_str){(*line_handler.line) + new_i + 1,
			end_var_name});
	len_right = (*max_i) - (*line_handler.i) - end_var_name;
	(*max_i) -= end_var_name + 1;
	if (var)
	{
		(*max_i) += var->value.len;
		new_i += var->value.len;
		new_str.len += var->value.len;
	}
	new_str.len += len_right + size_after_max_i;
	new_str.str = malloc(sizeof(char) * new_str.len);
	if (!new_str.str)
		return (-EXIT_FAILURE);
	new_str.str[*line_handler.i] = '\0';
	ft_memcpy(new_str.str, (*line_handler.line), (*line_handler.i));
	if (var)
		ft_memcpy(new_str.str + (*line_handler.i), var->value.str,
			var->value.len);
	ft_memcpy(new_str.str + new_i, (*line_handler.line) + (*line_handler.i)
		+ end_var_name + 1, size_after_max_i + 1);
	free((*line_handler.line));
	(*line_handler.line) = new_str.str;
	new_str.str = NULL;
	(*line_handler.i) = new_i;
	return (EXIT_SUCCESS);
}
