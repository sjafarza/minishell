/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/28 13:37:50 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_strchr_index_until_i(const char *s, int c, int i_max)
{
	int	i;

	i = -1;
	while (s[++i] && i < i_max)
		if ((unsigned char)s[i] == c)
			return (i);
	if ((unsigned char)s[i] == c && i < i_max)
		return (i);
	return (-EXIT_FAILURE);
}

int	ft_strchr_index(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if ((unsigned char)s[i] == c)
			return (i);
	if ((unsigned char)s[i] == c)
		return (i);
	return (-EXIT_FAILURE);
}
