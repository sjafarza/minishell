/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/03 16:43:44 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int		parse_back_slash(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;
	(*i)++;
	return (EXIT_SUCCESS);
}

int		parse_double_quote(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;
	return (EXIT_SUCCESS);
}

int		parse_simple_quote(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;
	return (EXIT_SUCCESS);
}

int		parse_type(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;
	return (SET_TYPE);
}

int		parse_type_wa(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;
	return (SET_TYPE_WITHOUT_ARGS);
}
