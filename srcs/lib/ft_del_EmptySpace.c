/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_EmptySpace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:31:19 by saray             #+#    #+#             */
/*   Updated: 2021/11/27 21:44:10 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_del_emptyspace(char *s)
{
	char	*r;
	int		i;
	int		j;
	int		k;
	int		len;

	i = 0;
	printf("line in ft_de_empty = %s\n", s);
	while (ft_is_blank(s[i]))
			i++;
	len = (int)ft_strlen(s);
	k = len - 1;
	while (ft_is_blank(s[k]))
			k--;
	if (i != 0 || k != (len - 1))
	{
		r = (char *)malloc(sizeof(char) * (len - (k -i + 1) + 1));
		if (!r)
			return ;
		j = -1;
		while (s[i] && i <= k)
			r[++j] = s[i++];
		r[++j] = '\0';
		free(s);
		s = ft_strdup(r);
	}

	printf("2 line in ft_de_empty = %s\n", s);
	
}

/*void	ft_del_emptyspace(char **s)
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
}*/
