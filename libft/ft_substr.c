/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/11 14:42:02 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_strnlen(const char *s, size_t len_max)
{
	size_t	i;

	i = 0;
	while (i < len_max && s[i] != '\0')
		i++;
	return (i);
}

static char	*ft_substr_int(const char *src, size_t len)
{
	char	*dst;

	dst = (char *)malloc(len * sizeof(char));
	if (dst != NULL)
		ft_strlcpy(dst, src, len);
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	size_t	len_int;
	size_t	len_final;

	if (!s)
		return (NULL);
	len_s = ft_strnlen(s, len + start);
	if (len_s < start)
		return (ft_strdup(""));
	else if (len_s < (start + len))
	{
		len_int = len_s - start;
		if (len < len_int)
			len_final = len;
		else
			len_final = len_int;
		return (ft_substr_int(s + start, len_final + 1));
	}
	return (ft_substr_int(s + start, len + 1));
}
/*
** Alloue (avec malloc(3)) et retourne une chaine de
** caracteres issue de la chaine donnee en argument
** Cette nouvelle chaine commence a l'index 'start' et
** a pour taille maximale 'len'
*/
