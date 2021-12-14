/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/14 15:50:56 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_array_once_ready(t_line line_handle, t_tmp_parsed tmp_parsed, int i, int did_find_parsing)
{
	if (((tmp_parsed.start == i && tmp_parsed.ac == 0) || *tmp_parsed.arg) && !did_find_parsing)
		return (EXIT_SUCCESS);
	if (tmp_parsed.start == i && !did_find_parsing)
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 1));
	else
		*tmp_parsed.arg = malloc(sizeof(char *) * (tmp_parsed.ac + 2));
	if (!(*tmp_parsed.arg))
		return (-EXIT_FAILURE);
	if (tmp_parsed.start != i || did_find_parsing)
	{
		(*tmp_parsed.arg)[tmp_parsed.ac] = ft_substr((*line_handle.line), tmp_parsed.start, i - tmp_parsed.start);
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

int	check_parsing(const t_parser dictionnary[MAX_PARSER], t_line line_handle, t_tmp_parsed tmp_parsed, t_parse_utils p_utils)
{
	while ((*p_utils.parse_i) < MAX_PARSER)
	{
		if (is_sequence_equal_to_parser_code(*p_utils.parse_i, (*line_handle.line) + (*p_utils.i)))
			return (dictionnary[*p_utils.parse_i].fun(&line_handle, &tmp_parsed, p_utils));
		(*p_utils.parse_i)++;
	}
	*p_utils.parse_i = -DID_NOTHING;
	return (EXIT_SUCCESS);
}

int	extract_next_arg(t_env *env, t_line line_handle, t_tmp_parsed tmp_parsed)
{
	int	i;
	int	ret;
	int	did_find_parsing;
	int	parse_i;

	ret = EXIT_SUCCESS;
	did_find_parsing = false;
	i = go_to_next_needed_i((*line_handle.line), &is_not_valid, tmp_parsed.start);
	tmp_parsed.start = i;
	while ((*line_handle.line)[i])
	{
		if (is_not_valid((*line_handle.line)[i]))
		{
			ret = extract_next_arg(env, line_handle, (t_tmp_parsed) {tmp_parsed.arg, tmp_parsed.ac + 1, tmp_parsed.type, i + 1, tmp_parsed.high_level_start});
			if (ret != EXIT_SUCCESS)
				return (ret);
			(*tmp_parsed.arg)[tmp_parsed.ac] = ft_substr(*line_handle.line, tmp_parsed.start, i - tmp_parsed.start);
			if (!(*tmp_parsed.arg)[tmp_parsed.ac])
			{
				free_array((*tmp_parsed.arg) + tmp_parsed.ac + 1);
				*tmp_parsed.arg = NULL;
				return (-EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		parse_i = 0;
		ret = check_parsing(g_parser_dictionary, line_handle, tmp_parsed, (t_parse_utils){env, &i, &parse_i});
		if (ret == ALREADY_FILLED)
			return (EXIT_SUCCESS);
		if (parse_i != DID_NOTHING)
			did_find_parsing = true;
		if (ret == PARSE_CUT)
			break;
		if (ret != EXIT_SUCCESS)
			return (ret);
		i++;
	}
	return (init_array_once_ready(line_handle, tmp_parsed, i, did_find_parsing));
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

	i = 0;
	while ((*line)[i])
	{
		i = go_to_next_needed_i((*line), &is_not_valid, i);
		start = i;
		type = TYPE_CMD;
		args = NULL;
		ret = extract_next_arg(env, (t_line){line, &i}, (t_tmp_parsed){&args, 0, &type, i, &start});
		if (ret != EXIT_SUCCESS)
			return (ret);
		if(type == TYPE_PIPE || type == TYPE_INPUT2)
		{
			if (args != NULL)
				if (add_back_parsed_groups_stack(env, args, TYPE_CMD) == -EXIT_FAILURE)
					return (-EXIT_FAILURE);
			args = init_array_with_one_str(ft_strdup(g_parser_dictionary[type].code.str));
			if (!args)
				return (-EXIT_FAILURE);
			if (add_back_parsed_groups_stack(env, args, type) == -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
		else if(type != TYPE_CMD)
		{
			if (!args || add_back_parsed_groups_stack(env, args, type) == -EXIT_FAILURE)
				return (-EXIT_FAILURE);
			printf("AH QUE COUCOU BOB FOR TYPE %d\n", type);
		}
		else if(args != NULL)
		{
			if (add_back_parsed_groups_stack(env, args, TYPE_CMD) == -EXIT_FAILURE)
				return (-EXIT_FAILURE);
		}
		printf("i is %d:%s:%s\n", i, (*line), (*line)+i);
		// else if (type != TYPE_CMD) 
		// {
		// 	// args = malloc(2 * sizeof(char *));
		// 	i = go_to_next_needed_i((*line), &is_valid, i);
		// 	// if (!args)
		// 	// 	return (-EXIT_FAILURE);
		// 	tmp = (*line)[i];
		// 	(*line)[i] = '\0';

		// 	args = init_array_with_one_str(ft_strdup((*line) + start));
		// 	if (!args)
		// 		return (-EXIT_FAILURE);
		// 	// args[0] = ft_strdup((*line) + start);
		// 	// args[1] = NULL;
		// 	// if (!args[0])
		// 	// 	return (-EXIT_FAILURE);
		// 	add_back_parsed_groups_stack(env, args, type);
		// 	(*line)[i] = tmp;
		// }
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
