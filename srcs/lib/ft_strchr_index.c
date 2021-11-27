/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/11/27 20:56:41 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

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
