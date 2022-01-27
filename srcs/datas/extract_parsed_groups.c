/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_parsed_groups.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2022/01/26 21:42:23 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	manage_type_pipe(t_env *env, char **args, int type)
{
	if (args != NULL)
		if (add_back_parsed_groups_stack(env, args, TYPE_CMD) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
	args = init_array_with_one_str(ft_strdup(
				g_parser_dictionary[type].code.str));
	if (!args)
		return (-EXIT_FAILURE);
	if (add_back_parsed_groups_stack(env, args, type) == -EXIT_FAILURE)
		return (-EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_results(t_env *env, char **args, int type)
{
	if (type == TYPE_PIPE)
	{
		if (manage_type_pipe(env, args, type) != EXIT_SUCCESS)
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
		if (add_back_parsed_groups_stack(env, args, TYPE_CMD) == -EXIT_FAILURE)
			return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
		if (check_results(env, args, type) != EXIT_SUCCESS)
			return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
