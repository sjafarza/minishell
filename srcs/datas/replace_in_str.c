/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/28 14:00:31 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	replace_in_str_until_i(t_env *env, char **str, int max_i)
{
	int			replaced_q;
	int			new_i;
	int			i;
	int			len_right;
	int			end_var_name;
	char		*new_str;
	int			new_len;
	t_env_var	*var;

	i = 0;
	new_len = 0;
	replaced_q = 0;
	while ((*str)[i] != '\0' && i < max_i)
	{
		if ((*str)[i] == '$')
		{
			new_len = i;
			new_i = i;
			i++;
			if (ft_isprint((*str)[i]) == false || ft_is_blank((*str)[i]) == true)
				continue;
			replaced_q++;
			end_var_name = ft_strchr_index_until_i((*str) + i, ' ', max_i - i);
			if (end_var_name < 0)
			{
				end_var_name = max_i - i;
				printf("DEFINE ERROR MANAGEMENT %d:%d:%d\n", end_var_name, max_i, i);
			}
			var = find_env_vars_t_str(env, (t_str){(*str) + i, end_var_name});
			len_right = max_i - i - end_var_name;
			max_i -= end_var_name + 1;
			if (var)
			{
				max_i += var->value.len;
				new_i += var->value.len;
				new_len += var->value.len;
			}
			new_len += len_right + 1;
			new_str = malloc(sizeof(char) * new_len);
			if (!new_str)
				return (-EXIT_FAILURE);
			new_str[0] = '\0';
			ft_strlcat(new_str, (*str), i);
			if (var)
				ft_strlcat(new_str, var->value.str, new_len);
			ft_strlcat(new_str, (*str) + i + end_var_name, new_len);
			free((*str));
			(*str) = new_str;
			new_str = NULL;
				printf("INTERMEDIRATE %d:%d:%d:%s\n", end_var_name, max_i, i, *str);
			i = new_i;

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
