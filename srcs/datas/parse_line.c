/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/03 21:37:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// #define HAS_MORE 1
// #define HAS_NO_MORE 0
// #define FOUND_ERROR -1
// #define FOUND_ERROR_PIPE -2

// int	find_any_from_set(char *line, char *set, int i)
// {
// 	int s_i;

// 	while (line[i])
// 	{
// 		s_i = 0;
// 		while (line[i] != set[s_i])
// 			s_i++;
// 		if (line[i] == set[s_i])
// 			return (i);
// 		i++;
// 	}
// 	return (i);
// }

int is_not_valid(char c)
{
	if (c && (ft_is_blank(c) || !ft_isprint(c)))
		return true;
	return false;
}
int is_valid(char c)
{
	if (c && !is_not_valid(c))
		return true;
	return false;
}

int	go_to_next_needed_i(char *line, int(*keep_going)(char), int i)
{
	while (keep_going(line[i]))
		i++;
	return (i);
}
// int	go_to_next_need_for_process_i(char *line, int i)
// {
// 	while (line[i] || line[i] == '\'' || line[i] == '"' || line[i] == '|');
// 	return (i);
// }

// int	extract_next_arg(char *line, int *i, char **arg)


int	init_array_once_ready(t_line line_handle, t_tmp_parsed tmp_parsed, int i)
{

	if (tmp_parsed.start == i && tmp_parsed.ac == 0)
		return (EXIT_SUCCESS);
	if (tmp_parsed.start == i)
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 1));
	else
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 2));
	if (!(*tmp_parsed.arg))
		return (-EXIT_FAILURE);
	if (tmp_parsed.start != i)
	{
		(*tmp_parsed.arg)[tmp_parsed.ac] = ft_strdup((*line_handle.line) + tmp_parsed.start);
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

int	check_parsing(t_line line_handle, t_tmp_parsed tmp_parsed, int *i)
{
	int	parse_i;

	parse_i = 0;
	while (parse_i < MAX_PARSER)
	{
		if (ft_strncmp(g_parser_dictionary[parse_i].code.str, (*line_handle.line) + (*i),
				g_parser_dictionary[parse_i].code.len) == 0)
			return (g_parser_dictionary[parse_i].fun(&line_handle, &tmp_parsed, i, parse_i));
		parse_i++;
	}
	return (EXIT_SUCCESS);
}

int	extract_next_arg(t_line line_handle, t_tmp_parsed tmp_parsed)//, int i, char ***arg, int ac, int *type)
{
	int	i;
	// int	parse_i;
	int ret;

	ret = EXIT_SUCCESS;
	i = go_to_next_needed_i((*line_handle.line), &is_not_valid, tmp_parsed.start);
	tmp_parsed.start = i;
	while ((*line_handle.line)[i])
	{
		if (is_not_valid((*line_handle.line)[i]))
		{
			ret = extract_next_arg(line_handle, (t_tmp_parsed) {tmp_parsed.arg, tmp_parsed.ac + 1, tmp_parsed.type, i + 1, tmp_parsed.high_level_start});
			if (ret != EXIT_SUCCESS)
				return (ret);
			(*line_handle.line)[i] = '\0';
			(*tmp_parsed.arg)[tmp_parsed.ac] = ft_strdup((*line_handle.line) + tmp_parsed.start);
			if (!(*tmp_parsed.arg)[tmp_parsed.ac])
			{
				free_array((*tmp_parsed.arg) + tmp_parsed.ac + 1);
				*tmp_parsed.arg = NULL;
				return (-EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		ret = check_parsing(line_handle, tmp_parsed, &i);
		if (ret == PARSE_CUT)
			break;
		if (ret != EXIT_SUCCESS)
			return (ret);
		// parse_i = 0;
		// while (parse_i < MAX_PARSER)
		// {
		// 	if (ft_strncmp(g_parser_dictionary[parse_i].code.str, (*line_handle.line) + i,
		// 			g_parser_dictionary[parse_i].code.len) == 0)
		// 	{
		// 		ret = g_parser_dictionary[parse_i].fun(&line_handle, &tmp_parsed, &i, parse_i);
		// 		if (ret != EXIT_SUCCESS && ret != PARSE_CUT)
		// 			return (ret);
		// 		break;
		// 	}
		// 	parse_i++;
		// }
		// if (ret == PARSE_CUT)
		// 	break;
		i++;
	}
	return init_array_once_ready(line_handle, tmp_parsed, i);
}

char	**init_array_with_one_str(char *s)
{
	char	**result;

	if(!s)
		return (NULL);
	result = malloc(2 * sizeof(char *));
	if(!result)
		return (NULL);
	result[0] = s;
	result[1] = NULL;
	return (result);
}

int	extract_parsed_groups(t_env *env, char **line)
{
	char **args;
	int	i;
	int	start;
	int type;
	int ret;
	char	tmp;

	i = 0;
	while ((*line)[i])
	{
		i = go_to_next_needed_i((*line), &is_not_valid, i);
		start = i;
		type = TYPE_CMD;
		args = NULL;
		ret = extract_next_arg((t_line){line, &i}, (t_tmp_parsed){&args, 0, &type, i, &start});
		if (ret == -EXIT_FAILURE)
			return (ret);
		if (args != NULL)
		{
			if (add_back_parsed_groups_stack(env, args, TYPE_CMD) == -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
		if(type == TYPE_PIPE)
		{
			args = init_array_with_one_str(ft_strdup("|"));
			if (!args)
				return (-EXIT_FAILURE);
			add_back_parsed_groups_stack(env, args, type);
		}
		else if (type != TYPE_CMD) 
		{
			// args = malloc(2 * sizeof(char *));
			i = go_to_next_needed_i((*line), &is_valid, i);
			// if (!args)
			// 	return (-EXIT_FAILURE);
			tmp = (*line)[i];
			(*line)[i] = '\0';

			args = init_array_with_one_str(ft_strdup((*line) + start));
			if (!args)
				return (-EXIT_FAILURE);
			// args[0] = ft_strdup((*line) + start);
			// args[1] = NULL;
			// if (!args[0])
			// 	return (-EXIT_FAILURE);
			add_back_parsed_groups_stack(env, args, type);
			(*line)[i] = tmp;
		}
	}
	return (EXIT_SUCCESS);
}

// int	get_next_args_rec(char *line, int *i, char ***args, int count)
// {
// 	int		res;
// 	char	*arg;

// 	res = extract_next_arg(line, i, &arg);
// 	if (res != HAS_MORE)
// 	{
// 		if (res <= FOUND_ERROR)
// 			return (res);
// 		*args = malloc(sizeof(char*) * (count + 2));
// 		if (!*args)
// 		{
// 			free(arg);
// 			return (FOUND_ERROR);
// 		}
// 		(*args)[count + 1] = NULL;
// 		(*args)[count] = arg;
// 		return (HAS_NO_MORE);
// 	}
// 	res = get_next_args_rec(line, i, args, count + 1);
// 	if (res <= FOUND_ERROR)
// 	{
// 		free(arg);
// 		return (res);
// 	}
// 	(*args)[count] = arg;
// 	return (HAS_NO_MORE);
// }

// int	parse_line(t_env *env, char *line)
// {
// 	int		i;
// 	int		res;
// 	char	**args;

// 	args = NULL;
// 	i = 0;
// 	res = get_next_args(line, i, &args);
// 	while (res == HAS_MORE)

// 	return (EXIT_SUCCESS);
// }
