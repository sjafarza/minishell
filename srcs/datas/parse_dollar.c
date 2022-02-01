/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 13:48:32 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_dollar_int(t_line *line_handle,
t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	end_var_name_abs;
	int	res;

	(void)tmp_parsed;
	end_var_name_abs = go_to_next_needed_i((*line_handle->line),
			&ft_is_valid_for_env_var_name, (*p_utils.i) + 1);
	if (end_var_name_abs == (*p_utils.i) + 1
		&& (*line_handle->line)[end_var_name_abs] == '?')
		end_var_name_abs++;
	if (end_var_name_abs == ((*p_utils.i) + 1))
		return (NOT_REPLACED);
	res = replace_in_str_one_var(p_utils.env,
			(t_line){line_handle->line, p_utils.i},
			end_var_name_abs - (*p_utils.i) - 1,
			ft_strlen(end_var_name_abs + (*line_handle->line)));
	if (res != EXIT_SUCCESS)
		return (res);
	return (REPLACED);
}

int	parse_dollar_for_double_quotes(t_line *line_handle,
t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	res;

	res = parse_dollar_int(line_handle, tmp_parsed, p_utils);
	if (res == REPLACED)
	{
		(*p_utils.i)--;
		return (EXIT_SUCCESS);
	}
	return (res);
}

int	parse_dollar(t_line *line_handle, t_tmp_parsed *tmp_parsed,
t_parse_utils p_utils)
{
	int	p_utils_i_memo;
	int	res;

	p_utils_i_memo = *(p_utils.i);
	res = parse_dollar_int(line_handle, tmp_parsed, p_utils);
	if (res == NOT_REPLACED)
		return (EXIT_SUCCESS);
	if (res != EXIT_SUCCESS)
		return (res);
	*(p_utils.do_not_parse_until) = *(p_utils.i);
	*(p_utils.i) = p_utils_i_memo - 1;
	if (p_utils_i_memo == tmp_parsed->start)
		tmp_parsed->start = (*(p_utils.i)) + 1;
	return (EXIT_SUCCESS);
}
