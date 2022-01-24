/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:19:36 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_array_once_ready(t_line line_handle, t_tmp_parsed tmp_parsed, int i,
	int did_find_parsing)
{
	if (((tmp_parsed.start == i && tmp_parsed.ac == 0) || *tmp_parsed.arg)
		&& !did_find_parsing)
		return (EXIT_SUCCESS);
	if (tmp_parsed.start == i && !did_find_parsing)
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 1));
	else
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 2));
	if (!(*tmp_parsed.arg))
		return (-EXIT_FAILURE);
	if (tmp_parsed.start != i || did_find_parsing)
	{
		(*tmp_parsed.arg)[tmp_parsed.ac] = ft_substr((*line_handle.line),
				tmp_parsed.start, i - tmp_parsed.start);
		if (!((*tmp_parsed.arg)[tmp_parsed.ac]))
		{
			free(*tmp_parsed.arg);
			*tmp_parsed.arg = NULL;
			return (-EXIT_FAILURE);
		}
		tmp_parsed.ac++;
	}
	(*tmp_parsed.arg)[tmp_parsed.ac] = NULL;
	if (i > (*line_handle.i))
		*line_handle.i = i;
	return (EXIT_SUCCESS);
}

char	**init_array_with_one_str(char *s)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc(2 * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = s;
	result[1] = NULL;
	return (result);
}
