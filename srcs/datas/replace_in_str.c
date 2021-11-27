/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 22:26:17 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	replace_in_str(t_env *env, char *(*str))
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
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '$')
		{
			new_len = i;
			new_i = i;
			i++;
			if ((*str)[i] == '\0')
				return (replaced_q);
			replaced_q++;
			end_var_name = ft_strchr_index((*str) + i, ' ');
			if (end_var_name < 0)
			{
				end_var_name = ft_strlen((*str) + i);
				printf("DEFINE ERROR MANAGEMENT %d\n", end_var_name);
			}
			var = find_env_vars_t_str(env, (t_str){(*str) + i, end_var_name});
			if (var)
			{
				new_i += var->value.len;
				new_len += var->value.len;
			}
			len_right = ft_strlen((*str) + i + end_var_name);
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
			i = new_i;
			continue;
		}
		i++;
	}
	return (replaced_q);
}
