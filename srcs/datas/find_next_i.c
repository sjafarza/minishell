/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:12 by saray             #+#    #+#             */
/*   Updated: 2021/12/04 10:34:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int is_not_valid(char c)
{
	if (c && (ft_is_blank(c) || !ft_isprint(c)))
		return true;
	return false;
}
int is_valid(char c)
{
	if (c && !is_not_valid(c))
		return true;
	return false;
}

int	go_to_next_needed_i(char *line, int(*keep_going)(char), int i)
{
	while (keep_going(line[i]))
		i++;
	return (i);
}
