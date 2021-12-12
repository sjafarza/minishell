/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sequence_equal_to_parser_code.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/12 19:37:21 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_sequence_equal_to_parser_code(int type_code, char *seq)
{
	if (!seq || type_code < 0)
		return (false);
	if (ft_strncmp(g_parser_dictionary[type_code].code.str, seq,
				g_parser_dictionary[type_code].code.len) == 0)
		return (true);
	return (false);
}
