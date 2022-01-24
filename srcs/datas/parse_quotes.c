/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:53:30 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	int	first_quote;
	int	last_quote;
	int	ret;
	int	parse_i;

	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line)
		+ first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = ft_strchr_index((const char *)((*line_handle->line)
				+ (*p_utils.i)),
			g_parser_dictionary[*p_utils.parse_i].code.str[0]);
	if (last_quote == -EXIT_FAILURE)
		return (INCOMPLETE_PATTERN);
	last_quote += (*p_utils.i);
	while (first_quote < last_quote)
	{
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary_for_doubles_quotes,
				*line_handle, tmp_parsed, (t_parse_utils){p_utils.env,
				p_utils.i,
				&parse_i, p_utils.do_not_parse_until});
		if (parse_i != DID_NOTHING)
		{
			if ((*line_handle->line)[*p_utils.i] ==
				*g_parser_dictionary[TYPE_DOUBLE_QUOTE].code.str)
			{
				last_quote = *p_utils.i;
				break ;
			}
			last_quote = (*p_utils.i)
				+ ft_strchr_index((const char *)((*line_handle->line)
						+ (*p_utils.i)),
					g_parser_dictionary[*p_utils.parse_i].code.str[0]);
			if (last_quote == -EXIT_FAILURE)
				return (INCOMPLETE_PATTERN);
		}
		else if (ret != EXIT_SUCCESS)
			return (ret);
		(*p_utils.i)++;
	}
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line)
		+ last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;
	return (EXIT_SUCCESS);
}

int	parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	int	first_quote;
	int	last_quote;

	(void)tmp_parsed;
	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line)
		+ first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = (*p_utils.i) + ft_strchr_index((*line_handle->line)
			+ (*p_utils.i), *(g_parser_dictionary[*p_utils.parse_i].code.str));
	if (last_quote == -EXIT_FAILURE)
		return (INCOMPLETE_PATTERN);
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line)
		+ last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;
	return (EXIT_SUCCESS);
}
