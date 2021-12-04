/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/02 10:27:11 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int		parse_back_slash(char **line_edited, int *i)
{
	(void)line_edited;
	(void)i;

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

int		replace_by_spaced(char **line_edited, int *i, char *replace)
{
	char	*tmp;
	char	*replace_ptr;

	if (*i == 0)
		replace_ptr = replace + 1;
	tmp = ft_str_insert(*line_edited, *i, replace_ptr);
	if(!tmp)
		return (-EXIT_FAILURE);
	free(*line_edited);
	*line_edited = tmp;
	*i = (*i) + ft_strlen(replace_ptr);
	return (EXIT_SUCCESS);
}

int		parse_pipe(char **line_edited, int *i)
{
	return (replace_by_spaced(line_edited, i, " | "));
}

int		parse_input1(char **line_edited, int *i)
{
	return (replace_by_spaced(line_edited, i, " < "));
}

int		parse_input2(char **line_edited, int *i)
{
	return (replace_by_spaced(line_edited, i, " << "));
}

int		parse_output1(char **line_edited, int *i)
{
	return (replace_by_spaced(line_edited, i, " > "));
}

int		parse_output2(char **line_edited, int *i)
{
	return (replace_by_spaced(line_edited, i, " >> "));
}
