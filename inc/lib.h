/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:47:17 by saray             #+#    #+#             */
/*   Updated: 2022/01/25 20:58:13 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include "./minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int		str_len(char const *s, char c);
int		ft_is_blank(char c);
char	*ft_strcat(const char *s1, const char *s2);
char	*ft_strcat_with_n(const char *s1, const char *s2);
char	*ft_str_insert(const char *s1, int i, const char *s2);

#endif
