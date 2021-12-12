/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/12 22:48:46 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_back_slash_int(char *line, int *i)
{
	if (!line[(*i) + 1])
		return (PARSE_INCOMPLETE);
	(*i)++;
	return (EXIT_SUCCESS);
}

int		parse_back_slash(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_int(*line_handle->line, p_utils.i));
}

int	find_next__quote(int id_quote, char *line, int i)
{
	if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, line + i))
		if (parse_back_slash_int(line, &i) != EXIT_SUCCESS)
			return (INCOMPLETE_PATTERN);
	while (line[i] && !is_sequence_equal_to_parser_code(id_quote, line + i))
	{
		if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, line + i))
			if (parse_back_slash_int(line, &i) != EXIT_SUCCESS)
				return (INCOMPLETE_PATTERN);
		i++;
	}
	if (!is_sequence_equal_to_parser_code(id_quote, line + i))
				return (INCOMPLETE_PATTERN);
	return (i);
}

int		parse__quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils, int (*fun)(t_env *, char **, int, int))
{
	int first;
	int last;
	int ret;

	(void)tmp_parsed;
	ret = EXIT_SUCCESS;
	first = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first, (*line_handle->line) + first + 1, ft_strlen((*line_handle->line) + first));
	last = find_next__quote(p_utils.parse_i, *line_handle->line, first);
	if (last == INCOMPLETE_PATTERN)
		return (INCOMPLETE_PATTERN);
	ft_strlcpy((*line_handle->line) + last, (*line_handle->line) + last + 1, ft_strlen((*line_handle->line) + last));
	last--;
	if(fun)
		ret = fun(p_utils.env, line_handle->line, first, last);

	printf("WHAT IS IT %d:%d:%d\n",*p_utils.i, first, last);

	*p_utils.i = last;

	return (ret);
}



int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	return (parse__quote(line_handle, tmp_parsed, p_utils, replace_in_str_between_min_i_and_max_i));
}

int		parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	return (parse__quote(line_handle, tmp_parsed, p_utils, NULL));
}

int		parse_type(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	*tmp_parsed->type = p_utils.parse_i;
	*line_handle->i = *p_utils.i;
	*tmp_parsed->high_level_start = tmp_parsed->start;
	tmp_parsed->start = *p_utils.i;
	return (PARSE_CUT);
}

int		parse_type_without_arg(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	*tmp_parsed->type = p_utils.parse_i;
	*line_handle->i = (*p_utils.i) + g_parser_dictionary[p_utils.parse_i].code.len;
	return (PARSE_CUT);
}

int	is_code_authorized_w1a(t_line *line_handle, int i)
{
	int	parse_i;

	parse_i = 0;
	while (parse_i < START_AUTHORISED_W1A)
	{
		if (ft_strncmp(g_parser_dictionary[parse_i].code.str, (*line_handle->line) + i,
				g_parser_dictionary[parse_i].code.len) == 0)
				return (-EXIT_FAILURE);
		parse_i++;
	}
	return (parse_i);
}

int get_arg_for_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	parse_i;
	int	ret;
	int start;

	start = *p_utils.i;
	while ((*line_handle->line)[*p_utils.i] && is_valid((*line_handle->line)[*p_utils.i]))
	{
		parse_i = is_code_authorized_w1a(line_handle, *p_utils.i);
		if (parse_i == -EXIT_FAILURE)
			break;
		ret = check_parsing(*line_handle, *tmp_parsed, p_utils);
		if (ret == PARSE_CUT)
			break;
		if (ret != EXIT_SUCCESS)
			return (ret);
		(*p_utils.i)++;
	}
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if ((*p_utils.i) == start)
	{
		(*tmp_parsed->arg)[tmp_parsed->ac] = NULL;
		return (-EXIT_FAILURE);
	}
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, start, (*p_utils.i) - start);
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free_array(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	return (EXIT_SUCCESS);
}

int		parse_type_w1a_only(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	ret;
	if (tmp_parsed->ac != 0 || (*tmp_parsed->high_level_start) != (*p_utils.i))
		return (PARSE_CUT);
	*tmp_parsed->type = p_utils.parse_i;
	(*p_utils.i) += g_parser_dictionary[p_utils.parse_i].code.len;
	if (!(*line_handle->line)[(*p_utils.i)])
		return (-EXIT_FAILURE);
	*tmp_parsed->arg = malloc(sizeof(char *) * 3);
	if (!(*tmp_parsed->arg))
		return (-EXIT_FAILURE);
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, tmp_parsed->start, (*p_utils.i) - tmp_parsed->start);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	*p_utils.i = go_to_next_needed_i((*line_handle->line), &is_not_valid, *p_utils.i);
	ret = get_arg_for_w1a(line_handle, tmp_parsed, p_utils);
	if (ret == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	if ((*p_utils.i) > (*line_handle->i))
		*line_handle->i = (*p_utils.i);
	return (PARSE_CUT);
}
