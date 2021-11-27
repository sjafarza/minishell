/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/11 14:46:56 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_blanks(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	return (i);
}

static int	set_sign(int *i, const char *str)
{
	if (str[*i] == '-')
	{
		(*i)++;
		return (-1);
	}
	else if (str[*i] == '+')
		(*i)++;
	return (1);
}

int	ft_atoi(const char *str)
{
	long	value;
	long	next_value;
	int		i;
	int		sign;

	value = 0;
	i = skip_blanks(str);
	sign = set_sign(&i, str);
	while (ft_isdigit(str[i]))
	{
		next_value = (value * 10) + (str[i] - '0');
		if (sign == -1 && next_value < 0)
			return (0);
		if (sign == 1 && next_value < 0)
			return (-1);
		value = next_value;
		i++;
	}
	return (value * sign);
}
