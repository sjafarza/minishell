/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_EmptySpace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:31:19 by saray             #+#    #+#             */
/*   Updated: 2021/11/21 13:35:45 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

void	ft_del_emptyspace(char **s)
{
	char	*r;
	int		i;
	int		j;
	int		k;

	k = -1;
	while (s[++k])
	{
		i = 0;
		while (s[k][i] == ' ' || s[k][i] == '\t' || s[k][i] == '\v' \
				|| s[k][i] == '\f' || s[k][i] == '\r')
			i++;
		if (i != 0)
		{
			r = (char *)malloc(sizeof(char) * (ft_strlen(s[k] - i) + 1));
			if (!r)
				return ;
			j = -1;
			while (s[k][i])
				r[++j] = s[k][i++];
			r[++j] = '\0';
			free(s[k]);
			s[k] = ft_strdup(r);
		}
	}
}
