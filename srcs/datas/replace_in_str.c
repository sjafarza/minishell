/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/21 09:19:12 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	replace_in_str_one_var(t_env *env, char **str, int *max_i, int *i, int size_after_max_i)
{
	int			new_i;
	int			len_right;
	int			end_var_name;
	t_str		new_str;
	t_env_var	*var;

	new_str.len = (*i);
	new_i = (*i);
	end_var_name = (*max_i) - (*i) - 1;
	var = find_env_vars_t_str(env, (t_str){(*str) + new_i + 1, end_var_name});
	len_right = (*max_i) - (*i) - end_var_name;
	(*max_i) -= end_var_name + 1;
	if (var)
	{
		(*max_i) += var->value.len;
		new_i += var->value.len;
		new_str.len += var->value.len;
	}
	new_str.len += len_right + size_after_max_i;
	new_str.str = malloc(sizeof(char) * new_str.len);
	if (!new_str.str)
		return (-EXIT_FAILURE);
	new_str.str[*i] = '\0';
	ft_memcpy(new_str.str, (*str), (*i));
	if (var)
		ft_memcpy(new_str.str + (*i), var->value.str, var->value.len);
	ft_memcpy(new_str.str + new_i, (*str) + (*i) + end_var_name + 1, size_after_max_i + 1);
	free((*str));
	(*str) = new_str.str;
	new_str.str = NULL;
	(*i) = new_i;
	return (EXIT_SUCCESS);
}

int	replace_in_str_between_min_i_and_max_i(t_env *env, char **str, int min_i, int max_i)
{
	int	size_after_max_i;

	size_after_max_i = ft_strlen((*str) + max_i);
	while (min_i < max_i && (*str)[min_i] != '\0')
	{
		if ((*str)[min_i] == '$')
		{
			min_i++;
			if (ft_isprint((*str)[min_i]) == false || ft_is_blank((*str)[min_i]) == true)
				continue;
printf("BEFORE REPLACING WITHOUT quote %d:%d:%s\n", min_i, max_i, *str);
			if (replace_in_str_one_var(env, str, &max_i, &min_i, size_after_max_i) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
			continue;
		}
		min_i++;
	}
	return (max_i);
}

int	replace_in_str(t_env *env, char **str)
{
	return (replace_in_str_between_min_i_and_max_i(env, str, 0, ft_strlen(*str)));
}
