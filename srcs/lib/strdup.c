/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 00:06:24 by saray             #+#    #+#             */
/*   Updated: 2021/11/14 00:06:31 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*string;
	
	i = 0;
	len = 0;
	while (s1[len])
		len++;
	string = (char *)malloc((len * sizeof(char)) + 1);
	if (string == NULL)
		return (NULL);
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
