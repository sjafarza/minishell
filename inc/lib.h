/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saray <saray.jafarzade@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2021/11/26 10:44:52 by saray            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include "./parser.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif



char	**ft_split(char const *s, char c);
char    *ft_substr(char const *s, unsigned int start, int len);
int      str_len(char const *s, char c);
char	*ft_strdup(const char *s1);
int     ft_memcmp(const void *s1, const void *s2, size_t n);
int	ft_strlen(char *s);
//void    ft_del_emptyspace(char **s);
void    ft_del_emptyspace(char *s);

#endif
