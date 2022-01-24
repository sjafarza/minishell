/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:53:19 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_arg_for_w1a(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
{
	int	parse_i;
	int	ret;
	int	start;
	int	did_find_parsing;

	did_find_parsing = false;
	start = *p_utils.i;
	while ((*line_handle->line)[*p_utils.i] &&
		is_valid((*line_handle->line)[*p_utils.i]))
	{
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary_for_w1a, *line_handle,
				tmp_parsed, (t_parse_utils){p_utils.env, p_utils.i, &parse_i,
				p_utils.do_not_parse_until});
		if (ret == PARSE_CUT)
			break ;
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
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_substr(*line_handle->line, start,
			(*p_utils.i) - start);
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free_array(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	return (EXIT_SUCCESS);
}

int	parse_type_w1a_only(t_line *line_handle, t_tmp_parsed *tmp_parsed,
	t_parse_utils p_utils)
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
	(*tmp_parsed->arg)[tmp_parsed->ac] = ft_strdup(
			g_parser_dictionary_for_w1a[*p_utils.parse_i].code.str);
	(*tmp_parsed->arg)[tmp_parsed->ac + 1] = NULL;
	if (!(*tmp_parsed->arg)[tmp_parsed->ac])
	{
		free(*tmp_parsed->arg);
		*tmp_parsed->arg = NULL;
		return (-EXIT_FAILURE);
	}
	tmp_parsed->ac++;
	*p_utils.i = go_to_next_needed_i((*line_handle->line), &is_not_valid,
			(*p_utils.i));
	ret = get_arg_for_w1a(line_handle, tmp_parsed, p_utils);
	if (ret != EXIT_SUCCESS)
		return (ret);
	if ((*p_utils.i) > (*line_handle->i))
		*line_handle->i = (*p_utils.i);
	return (ALREADY_FILLED);
}
