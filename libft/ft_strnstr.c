/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/11 14:44:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_size;

	i = -1;
	needle_size = ft_strlen(needle);
	if (needle_size == 0)
		return ((char *)haystack);
	while (++i < len && haystack[i] && i <= (len - needle_size))
		if (ft_strncmp(&haystack[i], needle, needle_size) == 0)
			return ((char *)&haystack[i]);
	return (NULL);
}
