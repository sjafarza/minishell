/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbfind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:09:25 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FOUND 0
#define NOT_FOUND 1
#define ERROR 2

static t_list_double	*ft_lstdbfind_int(t_list_double *lst, void *seek,
int (*find)(void*, void*))
{
	if (!lst || !find)
		return (NULL);
	if (find(seek, lst->content) == FOUND)
		return (lst);
	return (ft_lstdbfind_int(lst->next, seek, find));
}

int	ft_lstdbfind(t_list_double *head_src, t_list_double **found, void *seek,
int (*find)(void*, void*))
{
	if (!head_src)
		return (NOT_FOUND);
	if (!found)
		return (ERROR);
	*found = ft_lstdbfind_int(head_src, seek, find);
	if (!(*found))
		return (NOT_FOUND);
	return (FOUND);
}
