/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:03:58 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstdbmap_int(t_list_double *lst,
t_list_double *new_lst, void *(*f)(void *))
{
	if (!lst->next)
		return (0);
	new_lst->next = ft_lstdbnew((*f)(lst->next->content));
	if (!new_lst->next)
		return (-1);
	return (ft_lstdbmap_int(lst->next, new_lst->next, f));
}

t_list_double	*ft_lstdbmap(t_list_double *lst,
void *(*f)(void *), void (*del)(void *))
{
	t_list_double	*new_lst;

	if (!lst || !del || !f)
		return (NULL);
	new_lst = ft_lstdbnew((*f)(lst->content));
	if (!new_lst)
		return (NULL);
	if (ft_lstdbmap_int(lst, new_lst, f))
		ft_lstdbclear(&new_lst, del);
	return (new_lst);
}
