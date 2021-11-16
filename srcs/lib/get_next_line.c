/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 08:03:41 by saray             #+#    #+#             */
/*   Updated: 2021/11/14 18:33:26 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lib.h"

char	*ft_strjoin(char *s, char *t)
{
	int		i;
	int		j;
	char	*r;
	int		len;

	len = ft_strlen(s) + ft_strlen(t);
	i = 0;
	j = 0;
	r = (char *)malloc(sizeof(char) + (len + 1));
	if (!r)
		return (0);
	while (s[i])
	{
		r[i] = s[i];
		i++;
	}
	while (t[j])
	{
		r[i + j] = t[j];
		j++;
	}
	r[i + j] = 0;
	return (r);
}

/*char	*chek_gnl(int fd, char line, int BUFFER_SIZE)
{
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	str = (char *)malloc(sizeof(char) * 1);
	if (str)
		return (-1);
}*/
int	gnl(int fd, char **line)
{
	int		r;
	char	buf[2];
	char	*str;
	char	*tmp;


	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	str = (char *)malloc(sizeof(char) * 1);
	if (!str)
		return (-1);
	*str = 0;
	r = read(fd, &buf, BUFFER_SIZE - BUFFER_SIZE + 1);
	while (r)
	{
		buf[1] = 0;
		if (r == -1)
			return (-1);
		if (buf[0] == '\n')
			break ;
		tmp = str;
		str = ft_strjoin(str, buf);
		if (!str)
			return (-1);
		free(tmp);
		r = read(fd, &buf, BUFFER_SIZE - BUFFER_SIZE + 1);
	}
	*line = str;
	return (r);
}
