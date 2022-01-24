/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:53:35 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	forbidden_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)p_utils;
	return (-EXIT_FAILURE);
}

int	cut_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)p_utils;
	return (PARSE_CUT);
}

int	jump_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	(void)tmp_parsed;
	(void)p_utils;
	*line_handle->i = (*p_utils.i)
		+ g_parser_dictionary[*p_utils.parse_i].code.len;
	return (EXIT_SUCCESS);
}

int	parse_type(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	*tmp_parsed->type = *p_utils.parse_i;
	*line_handle->i = *p_utils.i;
	*tmp_parsed->high_level_start = tmp_parsed->start;
	tmp_parsed->start = *p_utils.i;
	return (PARSE_CUT);
}

int	parse_type_without_arg(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	*tmp_parsed->type = *p_utils.parse_i;
	*line_handle->i = (*p_utils.i)
		+ g_parser_dictionary[*p_utils.parse_i].code.len;
	return (PARSE_CUT);
}
