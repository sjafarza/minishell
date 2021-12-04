/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjafarza <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/12/02 08:19:42 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strcat(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*dst;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, s1_len + s2_len + 1);
	return (dst);
}

char	*ft_strcat_with_n(const char *s1, const char *s2)
{
	char *tmp;
	char *dst;

	tmp = ft_strcat(s1, "\n");
	if (!tmp)
		return (NULL);
	dst = ft_strcat(tmp, s2);
	free(tmp);
	return (dst);
}

char	*ft_str_insert(const char *s1, int i, const char *s2)
{
	char	*tmp;
	char	*dst;

	tmp = malloc(sizeof(char) * (i + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	ft_strlcpy(tmp, s1, i + 1);
	dst = ft_strcat(tmp, s2);
	free(tmp);
	tmp = dst;
	if (!tmp)
		return (NULL);
	dst = ft_strcat(tmp, s1 + i);
	free(tmp);
	return (dst);
}
