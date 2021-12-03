/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/03 21:37:07 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int		parse_back_slash(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)parse_i;
	(void)i;
	if (!(*line_handle->line)[(*i) + 1])
		return (PARSE_INCOMPLETE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)parse_i;
	(void)i;
	return (EXIT_SUCCESS);
}

int		parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)parse_i;
	(void)i;
	return (EXIT_SUCCESS);
}

int		parse_type(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	*tmp_parsed->type = parse_i;
	*line_handle->i = *i;
	*tmp_parsed->high_level_start = tmp_parsed->start;
	tmp_parsed->start = *i;
	return (PARSE_CUT);
}

int		parse_type_wa(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	(*line_handle->line)[(*i)] = '\0';
	*tmp_parsed->type = parse_i;
	*line_handle->i = (*i) + 1;
	return (PARSE_CUT);
}

int		parse_type_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	if (tmp_parsed->ac != 0)
		return (PARSE_CUT);

		
	(*line_handle->line)[(*i)] = '\0';
	*tmp_parsed->type = parse_i;
	*line_handle->i = (*i) + 1;
	return (PARSE_CUT);
}
