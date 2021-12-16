/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/16 20:03:58 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	parse_dollar(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	end_var_name;

	(void)tmp_parsed;
	end_var_name = go_to_next_needed_i((*line_handle->line), &ft_isalnum, (*p_utils.i) + 1);
	if (end_var_name == (*p_utils.i) + 1 && (*line_handle->line)[end_var_name] == '?')
		end_var_name++;
	end_var_name = replace_in_str_between_min_i_and_max_i(p_utils.env, line_handle->line, *p_utils.i, end_var_name);
	if (end_var_name == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	(*p_utils.i) = end_var_name - 1;
	return (EXIT_SUCCESS);
}

int		parse_type(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	*tmp_parsed->type = *p_utils.parse_i;
	*line_handle->i = *p_utils.i;
	*tmp_parsed->high_level_start = tmp_parsed->start;
	tmp_parsed->start = *p_utils.i;
	return (PARSE_CUT);
}

int		parse_type_without_arg(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	*tmp_parsed->type = *p_utils.parse_i;
	*line_handle->i = (*p_utils.i) + g_parser_dictionary[*p_utils.parse_i].code.len;
	return (PARSE_CUT);
}

int get_arg_for_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	parse_i;
	int	ret;
	int	start;
	int	did_find_parsing;

	did_find_parsing = false;
	start = *p_utils.i;
	while ((*line_handle->line)[*p_utils.i] && is_valid((*line_handle->line)[*p_utils.i]))
	{
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary_for_w1a, *line_handle, *tmp_parsed, (t_parse_utils){p_utils.env, p_utils.i, &parse_i});
		if (ret == PARSE_CUT)
			break;
		if (parse_i != DID_NOTHING)
			did_find_parsing = true;
		else if (ret != EXIT_SUCCESS)
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
	*tmp_parsed->type = *p_utils.parse_i;
	(*p_utils.i) += g_parser_dictionary[*p_utils.parse_i].code.len;
	if (!(*line_handle->line)[(*p_utils.i)])
		return (-EXIT_FAILURE);
	*tmp_parsed->arg = malloc(sizeof(char *) * 3);
	if (!(*tmp_parsed->arg))
		return (-EXIT_FAILURE);
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_strdup(g_parser_dictionary_for_w1a[*p_utils.parse_i].code.str);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	*p_utils.i = go_to_next_needed_i((*line_handle->line), &is_not_valid, (*p_utils.i));
	ret = get_arg_for_w1a(line_handle, tmp_parsed, p_utils);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if ((*p_utils.i) > (*line_handle->i))
		*line_handle->i = (*p_utils.i);
	return (ALREADY_FILLED);
}

int		forbidden_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)p_utils;
	return (-EXIT_FAILURE);
}

int		cut_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)p_utils;
	return (PARSE_CUT);
}

int		jump_parsing(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	(void)p_utils;
	*line_handle->i = (*p_utils.i) + g_parser_dictionary[*p_utils.parse_i].code.len;
	return (EXIT_SUCCESS);
}


#define INSIDE_QUOTE_BACKSLASH_ERASERS "$\\"


int	parse_back_slash_inside_quote(char **line, int *i, int quote_id)
{

	int increment;
	int delete;

	increment = 0;
	delete = false;
	while (INSIDE_QUOTE_BACKSLASH_ERASERS[increment])
	{
		if (INSIDE_QUOTE_BACKSLASH_ERASERS[increment] == (*line)[(*i) + 1])
		{
			delete = true;
			break;
		}
		increment++;
	}
	if (g_parser_dictionary[quote_id].code.str[0] == (*line)[(*i) + 1])
		delete = true;
	if (delete)
		ft_strlcpy((*line) + (*i), (*line) + (*i) + 1, ft_strlen((*line) + (*i)));
	(*i)++;
	return (EXIT_SUCCESS);
}

int		parse_back_slash_outside_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	if (!(*line_handle->line)[(*p_utils.i) + 1])
		return (INCOMPLETE_PATTERN);
	ft_strlcpy((*line_handle->line) + (*p_utils.i), (*line_handle->line) + (*p_utils.i) + 1, ft_strlen((*line_handle->line) + (*p_utils.i)));
	return (EXIT_SUCCESS);
}

int		parse_back_slash_inside_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_inside_quote(line_handle->line, p_utils.i, TYPE_QUOTE));
}

int		parse_back_slash_inside_double_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_inside_quote(line_handle->line, p_utils.i, TYPE_DOUBLE_QUOTE));
}


int	find_next__quote(int id_quote, char **line, int i)
{
	if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, (*line) + i))
		i++;
	while ((*line)[i] && !is_sequence_equal_to_parser_code(id_quote, (*line) + i))
	{
		if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, (*line) + i))
			i++;
		i++;
	}
	if (!is_sequence_equal_to_parser_code(id_quote, (*line) + i))
			return (INCOMPLETE_PATTERN);
	return (i);
}

int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	first_quote;
	int	last_quote;
	int	ret;
	int	parse_i;

	(void)tmp_parsed;
	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line) + first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = find_next__quote(*p_utils.parse_i, line_handle->line, first_quote);
	if (last_quote == INCOMPLETE_PATTERN)
		return (INCOMPLETE_PATTERN);
	while (first_quote < last_quote)
	{
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary_for_doubles_quotes, *line_handle, *tmp_parsed, (t_parse_utils){p_utils.env, p_utils.i, &parse_i});
		if (parse_i != DID_NOTHING)
		{
			if ((*line_handle->line)[*p_utils.i] == *g_parser_dictionary[TYPE_DOUBLE_QUOTE].code.str)
			{
				last_quote = *p_utils.i;
				break;
			}
			last_quote = find_next__quote(*p_utils.parse_i, line_handle->line, (*p_utils.i));
		}
		else if (ret != EXIT_SUCCESS)
			return (ret);
		(*p_utils.i)++;
	}
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line) + last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;
	return (EXIT_SUCCESS);
}

int	get_rid_of_first_backslash_per_sequence(char **line, int start, int last_quote)
{
	int ret;

	while (start < last_quote)
	{
		ret = ft_strchr_index((*line) + start, *(g_parser_dictionary[TYPE_BACK_SLASH].code.str));
		if (ret == -EXIT_FAILURE)
			break;
		start += ret;
		if (!(*line)[start + 1])
			break;
		if ((*line)[start + 1] != *(g_parser_dictionary[TYPE_BACK_SLASH].code.str))
		{
			start++;
			continue;
		}
		ft_strlcpy((*line) + start, (*line) + start + 1, ft_strlen((*line) + start));
		last_quote--;
		start++;
	}
	return (last_quote);
}

int		parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int first_quote;
	int last_quote;

	(void)tmp_parsed;
	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line) + first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = (*p_utils.i) + ft_strchr_index((*line_handle->line) + (*p_utils.i), *(g_parser_dictionary[*p_utils.parse_i].code.str));
	if (last_quote == -EXIT_FAILURE)
		return (INCOMPLETE_PATTERN);
	last_quote = get_rid_of_first_backslash_per_sequence(line_handle->line, first_quote, last_quote);
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line) + last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;	
	return (EXIT_SUCCESS);
}
