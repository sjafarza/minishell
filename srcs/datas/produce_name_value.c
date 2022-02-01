/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   produce_name_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 20:38:33 by saray             #+#    #+#             */
/*   Updated: 2022/02/01 16:11:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	produce_name_value(char *var, char **name, char **value)
{
	int	indx;

	*name = NULL;
	*value = NULL;
	indx = ft_strchr_index((const char *)var, '=');
	if (indx < 0)
	{
		*name = ft_strdup(var);
		if (*name == NULL)
			return (-EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	*name = ft_substr(var, 0, indx);
	if (*name == NULL)
		return (-EXIT_FAILURE);
	*value = ft_substr(var, indx + 1, ft_strlen(var) - indx);
	if (*value == NULL)
	{
		free(*name);
		*name = NULL;
		return (-EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
