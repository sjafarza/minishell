/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/29 18:23:51 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	replace_in_str_int(t_env *env, char **str, int *max_i, int *i)
{
	int			new_i;
	int			len_right;
	int			end_var_name;
	t_str		new_str;
	t_env_var	*var;

	new_str.len = (*i);
	new_i = (*i);
	end_var_name = ft_strchr_index_until_i((*str) + (*i), ' ', (*max_i) - (*i));
	if (end_var_name < 0)
	{
		end_var_name = (*max_i) - (*i);
		printf("DEFINE ERROR MANAGEMENT %d:%d:%d\n", end_var_name, (*max_i), (*i));
	}
	var = find_env_vars_t_str(env, (t_str){(*str) + (*i), end_var_name});
	len_right = (*max_i) - (*i) - end_var_name;
	(*max_i) -= end_var_name + 1;
	if (var)
	{
		(*max_i) += var->value.len;
		new_i += var->value.len;
		new_str.len += var->value.len;
	}
	new_str.len += len_right + 1;
	new_str.str = malloc(sizeof(char) * new_str.len);
	if (!new_str.str)
		return (-EXIT_FAILURE);
	new_str.str[0] = '\0';
	ft_strlcat(new_str.str, (*str), (*i));
	if (var)
		ft_strlcat(new_str.str, var->value.str, new_str.len);
	ft_strlcat(new_str.str, (*str) + (*i) + end_var_name, new_str.len);
	free((*str));
	(*str) = new_str.str;
	new_str.str = NULL;
	(*i) = new_i;
	return (EXIT_SUCCESS);
}

int	replace_in_str_until_i(t_env *env, char **str, int max_i)
{
	int			replaced_q;
	int			i;

	i = 0;
	replaced_q = 0;
	while (i < max_i && (*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
		{
			i++;
			if (ft_isprint((*str)[i]) == false || ft_is_blank((*str)[i]) == true)
				continue;

			if (replace_in_str_int(env, str, &max_i, &i) != EXIT_SUCCESS)
				return (-EXIT_FAILURE);
			replaced_q++;
			continue;
		}
		i++;
	}
	return (replaced_q);
}

int	replace_in_str(t_env *env, char **str)
{
	return (replace_in_str_until_i(env, str, ft_strlen(*str)));
}
