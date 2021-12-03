/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/03 09:35:32 by scarboni         ###   ########.fr       */
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

int	go_to_next_valid_i(char *line, int i)
{
	while (is_not_valid(line[i]))
		i++;
	return (i);
}
// int	go_to_next_need_for_process_i(char *line, int i)
// {
// 	while (line[i] || line[i] == '\'' || line[i] == '"' || line[i] == '|');
// 	return (i);
// }

// int	extract_next_arg(char *line, int *i, char **arg)
int	extract_next_arg(char **line, int i, char ***arg, int ac)
{
	int	start;
	int	parse_i;
	int ret;

	i = go_to_next_valid_i((*line), i);
	start = i;
	while ((*line)[i])
	{
		if (is_not_valid((*line)[i]))
		{
			ret = extract_next_arg(line, i + 1, arg, ac + 1);
			if (ret != EXIT_SUCCESS)
				return (ret);
			(*line)[i] = '\0';
			(*arg)[ac] = ft_strdup((*line) + start);
			if (!(*arg)[ac])
			{
				free_array((*arg) + ac + 1);
				return (-EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		parse_i = 0;
		printf("GOES HERE %d:%d\n", ac, i);
		if(i > 10)
			return -EXIT_FAILURE;
		while (parse_i < MAX_PARSER)
		{
		printf("GOES HERE parse_i:%d\n", parse_i);
			if (ft_strncmp(g_parser_dictionary[parse_i].code.str, (*line) + i,
					g_parser_dictionary[parse_i].code.len) == 0)
			{
				if (g_parser_dictionary[parse_i].fun(line, &i) != EXIT_SUCCESS)
					return (INCOMPLETE_PATTERN);
				break;
			}
			parse_i++;
		}
		i++;
	}
	if (start == i && ac == 0)
		return (EXIT_SUCCESS);
	if (start == i)
		*arg = malloc(sizeof(char *) * (ac + 1));
	else
		*arg = malloc(sizeof(char *) * (ac + 2));
	if (!(*arg))
		return (-EXIT_FAILURE);
	if (start != i)
	{
		(*arg)[ac] = ft_strdup((*line) + start);
		if (!((*arg)[ac]))
		{
			free(*arg);
			return (-EXIT_FAILURE);
		}
		ac++;
	}
	(*arg)[ac] = NULL;
	return (EXIT_SUCCESS);
}

int	extract_args(char **line, char ***arg)
{
	return (extract_next_arg(line, 0, arg, 0));
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
