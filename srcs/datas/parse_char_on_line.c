/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/04 14:50:29 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	// (*line_handle->line)[(*i)] = '\0';
	(void)line_handle;
	(void)tmp_parsed;
	(void)parse_i;
	(void)i;
	*tmp_parsed->type = parse_i;
	*line_handle->i = (*i) + g_parser_dictionary[parse_i].code.len;
	return (PARSE_CUT);
}

int get_arg_for_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i)
{
	int	parse_i;
	int	ret;
	int start;

	start = *i;
	while ((*line_handle->line)[*i] && is_valid((*line_handle->line)[*i]))
	{
		parse_i = 0;
		while (parse_i < START_AUTHORISED_W1A)
		{
			if (ft_strncmp(g_parser_dictionary[parse_i].code.str, *line_handle->line,
					g_parser_dictionary[parse_i].code.len) == 0)
			{
				ret = g_parser_dictionary[parse_i].fun(line_handle, tmp_parsed, i, parse_i);
				if (ret != EXIT_SUCCESS)
					return (ret);
			}
			parse_i++;
		}
		while (parse_i < MAX_PARSER)
		{
			if (ft_strncmp(g_parser_dictionary[parse_i].code.str, *line_handle->line,
					g_parser_dictionary[parse_i].code.len) == 0)
				return (-EXIT_FAILURE);
			parse_i++;
		}
		(*i)++;
	}
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, start, *i - start);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free_array(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	return (EXIT_SUCCESS);
}

int		parse_type_w1a_only(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	int	ret;

	if (tmp_parsed->ac != 0)
		return (PARSE_CUT);
	*tmp_parsed->type = parse_i;
	(*i) += g_parser_dictionary[parse_i].code.len;
	if (!(*line_handle->line)[(*i)])
		return (-EXIT_FAILURE);
	*tmp_parsed->arg = malloc(sizeof(char *) * 3);
	if (!(*tmp_parsed->arg))
		return (-EXIT_FAILURE);
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, tmp_parsed->start, (*i) - tmp_parsed->start);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	*i = go_to_next_needed_i((*line_handle->line), &is_not_valid, *i);
	ret = get_arg_for_w1a(line_handle, tmp_parsed, i);
	if (ret == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if ((*i) > (*line_handle->i))
		*line_handle->i = (*i);
	return (PARSE_CUT);
}

int		parse_type_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, int *i, int parse_i)
{
	int	ret;
	printf("HELLO STARTING %s:%d:%d\n", *line_handle->line,*i, tmp_parsed->ac );

	printf("Ah que cc bob %d:%d:%s:%s\n", *i, *tmp_parsed->high_level_start, (*line_handle->line) + *i, (*line_handle->line));

	if (tmp_parsed->ac != 0)
	{
		*i = *tmp_parsed->high_level_start;
		// *tmp_parsed->high_level_start = *i ;
		return (PARSE_CUT);
	}
	if (tmp_parsed->ac != 0)
		return (PARSE_CUT);
	*tmp_parsed->type = parse_i;
	(*i) += g_parser_dictionary[parse_i].code.len;
	if (!(*line_handle->line)[(*i)])
		return (-EXIT_FAILURE);
	*tmp_parsed->arg = malloc(sizeof(char *) * 3);
	if (!(*tmp_parsed->arg))
		return (-EXIT_FAILURE);
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, tmp_parsed->start, (*i) - tmp_parsed->start);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	*i = go_to_next_needed_i((*line_handle->line), &is_not_valid, *i);
	ret = get_arg_for_w1a(line_handle, tmp_parsed, i);
	if (ret == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if ((*i) > (*line_handle->i))
		*line_handle->i = (*i);
	return (PARSE_CUT);
}
