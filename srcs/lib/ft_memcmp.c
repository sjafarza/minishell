/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 23:28:29 by saray             #+#    #+#             */
/*   Updated: 2021/11/13 23:29:42 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dst1;
	const unsigned char	*dst2;
	size_t				i;

	dst1 = (const unsigned char *)s1;
	dst2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (dst1[i] != dst2[i])
			return (dst1[i] - dst2[i]);
		i++;
	}
	return (0);
}
