/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/24 22:07:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	extract_next_arg(t_env *env, t_line line_handle, t_tmp_parsed tmp_parsed,
		int do_not_parse_until);

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

int	check_parsing(const t_parser dictionnary[MAX_PARSER], t_line line_handle,
	t_tmp_parsed *tmp_parsed, t_parse_utils p_utils)
{
	while ((*p_utils.parse_i) < MAX_PARSER)
	{
		if (is_sequence_equal_to_parser_code(*p_utils.parse_i,
				(*line_handle.line) + (*p_utils.i)))
			return (dictionnary[*p_utils.parse_i].fun(&line_handle,
					tmp_parsed, p_utils));
		(*p_utils.parse_i)++;
	}
	*p_utils.parse_i = -DID_NOTHING;
	return (EXIT_SUCCESS);
}

typedef struct s_norm
{
	int	*i;
	int	*do_not_parse_until;
	int	*did_find_parsing;
}	t_norm;

int	extract_next_arg_int_rec(t_env *env, t_line line_handle,
	t_tmp_parsed tmp_parsed, t_norm norm)
{
	int	ret;

	ret = extract_next_arg(env, line_handle, (t_tmp_parsed)
		{tmp_parsed.arg, tmp_parsed.ac + 1, tmp_parsed.type, *(norm.i) + 1,
			tmp_parsed.high_level_start}, *(norm.do_not_parse_until));
	if (ret != EXIT_SUCCESS)
		return (ret);
	(*tmp_parsed.arg)[tmp_parsed.ac] = ft_substr(*line_handle.line,
			tmp_parsed.start, *(norm.i) - tmp_parsed.start);
	if (!(*tmp_parsed.arg)[tmp_parsed.ac])
	{
		free_array((*tmp_parsed.arg) + tmp_parsed.ac + 1);
		*tmp_parsed.arg = NULL;
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

typedef struct s_norm_loop
{
	int	action;
	int	ret;
}	t_norm_loop;

#define CONTINUE	1
#define BREAK		2
#define DO_RETURN	3
#define NOTHING		4

t_norm_loop	extract_next_arg_loop(t_env *env, t_line line_handle,
	t_tmp_parsed *tmp_parsed, t_norm norm)
{
	int	parse_i;
	int	ret;

	if (is_not_valid((*line_handle.line)[*(norm.i)]))
	{
		if (*(norm.did_find_parsing) == false && tmp_parsed->start
			== *(norm.i))
		{
			*(norm.i) = go_to_next_needed_i((*line_handle.line),
					&is_not_valid, tmp_parsed->start);
			tmp_parsed->start = *(norm.i);
			return ((t_norm_loop){CONTINUE, 0});
		}
		return ((t_norm_loop){DO_RETURN, extract_next_arg_int_rec(env,
				line_handle, *tmp_parsed, norm)});
	}
	parse_i = 0;
	if (*(norm.do_not_parse_until) <= *(norm.i))
	{
		ret = check_parsing(g_parser_dictionary, line_handle, tmp_parsed,
				(t_parse_utils){env, norm.i, &parse_i,
				norm.do_not_parse_until});
		if (ret == ALREADY_FILLED)
			return ((t_norm_loop){DO_RETURN, EXIT_SUCCESS});
		if (parse_i == TYPE_QUOTE || parse_i == TYPE_DOUBLE_QUOTE)
			*(norm.did_find_parsing) = true;
		if (ret == PARSE_CUT)
			return ((t_norm_loop){BREAK, 0});
		if (ret != EXIT_SUCCESS)
			return ((t_norm_loop){DO_RETURN, ret});
	}
	return ((t_norm_loop){NOTHING, 0});
}

int	extract_next_arg(t_env *env, t_line line_handle, t_tmp_parsed tmp_parsed,
int do_not_parse_until)
{
	int			i;
	int			did_find_parsing;
	t_norm_loop	result_loop;

	did_find_parsing = false;
	i = go_to_next_needed_i((*line_handle.line), &is_not_valid,
			tmp_parsed.start);
	tmp_parsed.start = i;
	while ((*line_handle.line)[i])
	{	
		result_loop = extract_next_arg_loop(env, line_handle, &tmp_parsed,
				(t_norm){&i, &do_not_parse_until, &did_find_parsing});
		if (result_loop.action == CONTINUE)
			continue ;
		else if (result_loop.action == BREAK)
			break ;
		else if (result_loop.action == DO_RETURN)
			return (result_loop.ret);
		i++;
	}
	return (init_array_once_ready(line_handle, tmp_parsed, i,
			did_find_parsing));
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

int	extract_parsed_groups(t_env *env, char **line)
{
	char	**args;
	int		i;
	int		start;
	int		type;
	int		ret;

	i = 0;
	while ((*line)[i])
	{
		i = go_to_next_needed_i((*line), &is_not_valid, i);
		start = i;
		type = TYPE_CMD;
		args = NULL;
		ret = extract_next_arg(env, (t_line){line, &i}, (t_tmp_parsed)
			{&args, 0, &type, i, &start}, -1);
		if (ret != EXIT_SUCCESS)
			return (ret);
		if (type == TYPE_PIPE)
		{
			if (args != NULL)
				if (add_back_parsed_groups_stack(env, args, TYPE_CMD)
					== -EXIT_FAILURE)
					return (-EXIT_FAILURE);
			args = init_array_with_one_str(ft_strdup(
						g_parser_dictionary[type].code.str));
			if (!args)
				return (-EXIT_FAILURE);
			if (add_back_parsed_groups_stack(env, args, type)
				== -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
		else if (type != TYPE_CMD)
		{
			if (!args || add_back_parsed_groups_stack(env, args, type)
				== -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
		else if (args != NULL)
		{
			if (add_back_parsed_groups_stack(env, args, TYPE_CMD)
				== -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
