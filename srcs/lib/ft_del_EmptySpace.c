/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_EmptySpace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:31:19 by saray             #+#    #+#             */
/*   Updated: 2021/11/18 12:36:33 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

void	ft_del_EmptySpace(char **s)
{
	char    *r;
	int     i;
	int     l;
	int     j;
	int     k;
	
	k = -1;
	while (s[++k])
	{
		i = 0;
		l = ft_strlen(s[k]);
		while (s[k][i] == ' ' || s[k][i] == '\t' || s[k][i] == '\v' \
				|| s[k][i] == '\f' || s[k][i] == '\r')
			i++;
		l -= i;
		r = (char *)malloc(sizeof(char) * l + 1);
		j = -1;
		while (s[k][i])
		{
			r[++j] = s[k][i];
			i++;
		}
		r[++j] = '\0';
		free(s[k]);
		s[k] = ft_strdup(r);
	}
}
