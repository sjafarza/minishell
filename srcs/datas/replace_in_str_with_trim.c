/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str_with_trim.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:37:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	return_and_clean(t_env_var *var, t_str var_trimmed, int code)
{
	if (var && var_trimmed.str)
		free(var_trimmed.str);
	return (code);
}

int	replace_in_str_one_var_with_trim(t_env *env, t_line line_handler,
int end_var_name, int size_after_max_i)
{
	int			new_i;
	t_str		new_str;
	t_env_var	*var;
	t_str		var_trimmed;

	new_str.len = (*line_handler.i);
	new_i = (*line_handler.i);
	var = find_env_vars_t_str(env, (t_str){(*line_handler.line) + new_i + 1,
			end_var_name});
	if (var)
	{
		init_t_str(&var_trimmed, ft_strtrim(var->value.str, BLANK_CHARS));
		new_str.len += var_trimmed.len;
	}
	new_str.len += size_after_max_i + 1;
	new_str.str = malloc(sizeof(char) * new_str.len);
	if (!new_str.str)
		return (return_and_clean(var, var_trimmed, -EXIT_FAILURE));
	ft_memcpy(new_str.str, (*line_handler.line), (*line_handler.i));
	if (var)
	{
		new_i += var_trimmed.len;
		ft_memcpy(new_str.str + (*line_handler.i), var_trimmed.str,
			var_trimmed.len);
	}
	ft_memcpy(new_str.str + new_i, (*line_handler.line) + (*line_handler.i)
		+ end_var_name + 1, size_after_max_i + 1);
	free((*line_handler.line));
	(*line_handler.line) = new_str.str;
	(*line_handler.i) = new_i;
	if (var && ft_is_blank(var->value.str[var->value.len - 1]))
		return (return_and_clean(var, var_trimmed, PARSE_CUT));
	return (return_and_clean(var, var_trimmed, EXIT_SUCCESS));
}
