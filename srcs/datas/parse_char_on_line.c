/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_char_on_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/14 15:57:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

#define INSIDE_QUOTE_BACKSLASH_ERASERS "$\\"

int	parse_back_slash_inside_quote(char **line, int *i, int quote_id)
{
	int increment;
	int delete;

	if (!(*line)[(*i) + 1])
		return (INCOMPLETE_PATTERN);
	increment = 0;
	delete = false;
	while(INSIDE_QUOTE_BACKSLASH_ERASERS[increment])
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

int	parse_dollar(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)line_handle;
	(void)tmp_parsed;
	(void)p_utils;
	int end_var_name;

	end_var_name = go_to_next_needed_i((*line_handle->line), &ft_isalnum, (*p_utils.i) + 1);
	end_var_name = replace_in_str_between_min_i_and_max_i(p_utils.env, line_handle->line, *p_utils.i, end_var_name);
	if (end_var_name == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	(*p_utils.i) = end_var_name - 1;
	return (EXIT_SUCCESS);
}

int	parse_back_slash_outside_quote(char **line, int *i)
{
	if (!(*line)[(*i) + 1])
		return (INCOMPLETE_PATTERN);
	ft_strlcpy((*line) + (*i), (*line) + (*i) + 1, ft_strlen((*line) + (*i)));
	(*i)++;
	return (EXIT_SUCCESS);
}

// int		parse_back_slash(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
// {
// 	(void)tmp_parsed;
// 	return (parse_back_slash_outside_quote(line_handle->line, p_utils.i));
// }

int	find_next__quote(int id_quote, char **line, int i)
{
	if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, (*line) + i))
		if (parse_back_slash_inside_quote(line, &i, id_quote) != EXIT_SUCCESS)
			return (INCOMPLETE_PATTERN);
	while ((*line)[i] && !is_sequence_equal_to_parser_code(id_quote, (*line) + i))
	{
		if (is_sequence_equal_to_parser_code(TYPE_BACK_SLASH, (*line) + i))
			if (parse_back_slash_inside_quote(line, &i, id_quote) != EXIT_SUCCESS)
				return (INCOMPLETE_PATTERN);
		i++;
	}
	if (!is_sequence_equal_to_parser_code(id_quote, (*line) + i))
				return (INCOMPLETE_PATTERN);
	return (i);
}

// int replace_fun(t_line *line_handle, t_parse_utils p_utils, int first_quote, int last_quote)
// {
// 	int end_var_name;
// 	int	end_var_name_dup;

// 	while (first_quote < last_quote)
// 	{
// 		end_var_name = go_to_next_needed_i((*line_handle.line), &is_valid_for_var_name, (*line_handle.i)) - (*line_handle.i);
// 		end_var_name_dup = end_var_name;
// 		end_var_name = replace_in_str_between_min_i_and_max_i(p_utils.env, line_handle->line, first_quote, end_var_name);
// 		if (end_var_name == -EXIT_FAILURE)
// 			return (-EXIT_FAILURE);
// 		last_quote += end_var_name - end_var_name_dup;
// 		first_quote = end_var_name;
// 	}
// 	return (last_quote);
// }

int		parse__quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils, int replace)
{
	int first_quote;
	int last_quote;
	

	(void)tmp_parsed;
	first_quote = *p_utils.i;
	ft_strlcpy((*line_handle->line) + first_quote, (*line_handle->line) + first_quote + 1, ft_strlen((*line_handle->line) + first_quote));
	last_quote = find_next__quote(*p_utils.parse_i, line_handle->line, first_quote);
	if (last_quote == INCOMPLETE_PATTERN)
		return (INCOMPLETE_PATTERN);
	ft_strlcpy((*line_handle->line) + last_quote, (*line_handle->line) + last_quote + 1, ft_strlen((*line_handle->line) + last_quote));
	if (replace)
	{
		// last_quote = replace_fun(line_handle, p_utils, first_quote, last_quote);
		// if (last_quote == -EXIT_FAILURE)
		// 	return (last_quote);
	}
	(*p_utils.i) = last_quote - 1;
	return (EXIT_SUCCESS);
}




int		parse_double_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	return (parse__quote(line_handle, tmp_parsed, p_utils, true));
}

int		parse_simple_quote(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	return (parse__quote(line_handle, tmp_parsed, p_utils, false));
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

// int	is_code_authorized_w1a(t_line *line_handle, int i)
// {
// 	int	parse_i;

// 	parse_i = 0;
// 	while (parse_i < START_AUTHORISED_W1A)
// 	{
// 		if (ft_strncmp(g_parser_dictionary[parse_i].code.str, (*line_handle->line) + i,
// 				g_parser_dictionary[parse_i].code.len) == 0)
// 				return (-EXIT_FAILURE);
// 		parse_i++;
// 	}
// 	return (parse_i);
// }

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
	// *p_utils.i += g_cmd_dictionary[*p_utils.parse_i].code.len;
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
	if (ret == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
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



int		parse_back_slash_outside_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_outside_quote(line_handle->line, p_utils.i));
}

int		parse_back_slash_inside_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_outside_quote(line_handle->line, p_utils.i));
}

int		parse_back_slash_inside_double_quotes(t_line *line_handle, t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	(void)tmp_parsed;
	return (parse_back_slash_outside_quote(line_handle->line, p_utils.i));
}
