/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbfind_index.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:07:09 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FOUND 0
#define NOT_FOUND -1
#define ERROR -2

static int	ft_lstdbfind_index_int(t_list_double *lst, void *seek,
int (*find)(void*, void*))
{
	int	tmp;

	if (!lst || !find)
		return (ERROR);
	if (find(seek, lst->content) == FOUND)
		return (FOUND);
	tmp = ft_lstdbfind_index_int(lst->next, seek, find);
	if (tmp == ERROR)
		return (ERROR);
	return (tmp + 1);
}

int	ft_lstdbfind_index(t_list_double *head_src, void *seek,
int (*find)(void*, void*))
{
	if (!head_src)
		return (NOT_FOUND);
	return (ft_lstdbfind_index_int(head_src, seek, find));
}
