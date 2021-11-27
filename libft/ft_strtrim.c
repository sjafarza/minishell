/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/11 18:42:28 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_equal_to(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_end_trimmed(char const *s1, char const *set, size_t len)
{
	size_t	i;

	i = 1;
	while (is_equal_to(s1[len - i], set) && i < len)
		i++;
	return (i - 1);
}

static char	*ft_strtrim_int_mini(void)
{
	char	*trimed;

	trimed = (char *)malloc(sizeof(char));
	trimed[0] = '\0';
	return (trimed);
}

static char	*ft_strtrim_int_full(size_t len, size_t start, char const *s1,
char const *set)
{
	int		size_new_s;
	int		j;
	size_t	end;
	char	*trimed;

	end = get_end_trimmed(s1, set, len);
	if ((start + end) > len)
		return (NULL);
	size_new_s = len - (start + end);
	j = 0;
	trimed = (char *)malloc((1 + size_new_s) * sizeof(char));
	if (!trimed)
		return (NULL);
	while (start < len - end && s1[start])
	{
		trimed[j] = s1[start];
		start++;
		j++;
	}
	trimed[j] = '\0';
	return (trimed);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	len = ft_strlen(s1);
	start = 0;
	while (is_equal_to(s1[start], set) && s1[start] != '\0')
		start++;
	if (start == len)
		return (ft_strtrim_int_mini());
	return (ft_strtrim_int_full(len, start, s1, set));
}

/*
** Alloue (avec malloc(3)) et retourne une copie de la
** chaine de caracteres donnee en argument, sans les
** caracteres specifies dans le set donne en argument
** au debut et a la fin de la chaine de caracteres.
*/
