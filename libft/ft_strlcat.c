/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/10 20:00:08 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t len_max)
{
	size_t	i;

	i = 0;
	while (i < len_max && s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dst_len_mx)
{
	size_t	dst_len;
	size_t	dst_len_mx_updated;

	dst_len = ft_strnlen(dst, dst_len_mx);
	dst_len_mx_updated = dst_len_mx - dst_len;
	if (dst_len_mx_updated == 0)
		return (dst_len_mx + ft_strlen(src));
	return (ft_strlcpy(&dst[dst_len], src, dst_len_mx_updated) + dst_len);
}
