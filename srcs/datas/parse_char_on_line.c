/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/20 14:07:04 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


int		parse_dollar_for_double_quotes(t_line *line_handle,
t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	end_var_name_abs;
	int	res;

	(void)tmp_parsed;
	end_var_name_abs = go_to_next_needed_i((*line_handle->line), &ft_isalnum, (*p_utils.i) + 1);
	if (end_var_name_abs == (*p_utils.i) + 1 && (*line_handle->line)[end_var_name_abs] == '?')
		end_var_name_abs++;
	if (end_var_name_abs == ((*p_utils.i) + 1))
		return (EXIT_SUCCESS);
	res = replace_in_str_one_var(p_utils.env, (t_line){line_handle->line, p_utils.i},
		end_var_name_abs - (*p_utils.i) - 1, ft_strlen(end_var_name_abs + (*line_handle->line)));
	if (res != EXIT_SUCCESS)
		return (res);
	(*p_utils.i)--;
	return (EXIT_SUCCESS);
}

//Mauvaise gestion des var dans ce cas là, a revoir 
int	parse_dollar(t_line *line_handle, t_tmp_parsed *tmp_parsed,
t_parse_utils p_utils)
{
	int	p_utils_i_memo;
	int	res;

	p_utils_i_memo = *(p_utils.i);
	res = parse_dollar_for_double_quotes(line_handle, tmp_parsed, p_utils);

	
	*(p_utils.i) = go_to_next_needed_i(*(line_handle->line), &is_not_valid, p_utils_i_memo) - 1;
	if (p_utils_i_memo == tmp_parsed->start)
		tmp_parsed->start = (*(p_utils.i)) + 1;
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
		ret = check_parsing(g_parser_dictionary_for_w1a, *line_handle, tmp_parsed, (t_parse_utils){p_utils.env, p_utils.i, &parse_i});
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

int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	int	first_quote;
	int	last_quote;
	int	ret;
	int	parse_i;

	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line) + first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = ft_strchr_index((const char *)((*line_handle->line) + (*p_utils.i)), g_parser_dictionary[*p_utils.parse_i].code.str[0]);
	if (last_quote == -EXIT_FAILURE)
		return (INCOMPLETE_PATTERN);
	last_quote += (*p_utils.i);
	while (first_quote < last_quote)
	{
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary_for_doubles_quotes, *line_handle, tmp_parsed, (t_parse_utils){p_utils.env, p_utils.i, &parse_i});
		if (parse_i != DID_NOTHING)
		{
			if ((*line_handle->line)[*p_utils.i] == *g_parser_dictionary[TYPE_DOUBLE_QUOTE].code.str)
			{
				last_quote = *p_utils.i;
				break;
			}
			last_quote = (*p_utils.i) + ft_strchr_index((const char *)((*line_handle->line) + (*p_utils.i)), g_parser_dictionary[*p_utils.parse_i].code.str[0]);
			if (last_quote == -EXIT_FAILURE)
				return (INCOMPLETE_PATTERN);
		}
		else if (ret != EXIT_SUCCESS)
			return (ret);
		(*p_utils.i)++;
	}
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line) + last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;
	return (EXIT_SUCCESS);
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
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line) + last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	(*p_utils.i) = last_quote - 1;	
	return (EXIT_SUCCESS);
}
