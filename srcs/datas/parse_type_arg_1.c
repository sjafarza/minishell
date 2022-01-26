/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_arg_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/26 21:20:20 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_type_w1a_only_double_input(t_line *line_handle,
	t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	return (parse_type_w1a_only_int(line_handle, tmp_parsed,
			p_utils, g_parser_dictionary_for_w1a_double_input));
}

int	parse_type_w1a_only(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	return (parse_type_w1a_only_int(line_handle, tmp_parsed,
			p_utils, g_parser_dictionary_for_w1a));
}
