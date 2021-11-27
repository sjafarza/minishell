/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/10 20:16:17 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	strlen_from_int(int value, int sign)
{
	size_t	result;

	result = 0;
	if (sign == -1)
		result++;
	else if (value == 0)
		return (1);
	while (value != 0)
	{
		value = value / 10;
		result++;
	}
	return (result);
}

static char	*ft_itoa_int(int n, int buf, int min_i, int sign)
{
	size_t	len;
	int		i;
	char	*str;

	len = strlen_from_int(n, sign);
	i = len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	str[len] = '\0';
	while (--i >= min_i)
	{
		str[i] = '0' + (n % 10);
		n = n / 10;
	}
	str[len - 1] += buf;
	return (str);
}

char	*ft_itoa(int n)
{
	if (n < 0)
	{
		if (n - 1 > 0)
			return (ft_itoa_int(-(n + 1), 1, 1, -1));
		return (ft_itoa_int(-n, 0, 1, -1));
	}
	else
		return (ft_itoa_int(n, 0, 0, 1));
}
