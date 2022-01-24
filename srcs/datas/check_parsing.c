/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:14:28 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_parsing(const t_parser dictionnary[MAX_PARSER], t_line line_handle,
	t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	while ((*p_utils.parse_i) < MAX_PARSER)
	{
		if (is_sequence_equal_to_parser_code(*p_utils.parse_i,
				(*line_handle.line) + (*p_utils.i)))
			return (dictionnary[*p_utils.parse_i].fun(&line_handle,
					tmp_parsed, p_utils));
		(*p_utils.parse_i)++;
	}
	*p_utils.parse_i = -DID_NOTHING;
	return (EXIT_SUCCESS);
}
