/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/10 20:22:27 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstmap_int(t_list *lst, t_list *new_lst, void *(*f)(void *))
{
	if (!lst->next)
		return (0);
	new_lst->next = ft_lstnew((*f)(lst->next->content));
	if (!new_lst->next)
		return (-1);
	return (ft_lstmap_int(lst->next, new_lst->next, f));
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;

	if (!lst || !del || !f)
		return (NULL);
	new_lst = ft_lstnew((*f)(lst->content));
	if (!new_lst)
		return (NULL);
	if (ft_lstmap_int(lst, new_lst, f))
		ft_lstclear(&new_lst, del);
	return (new_lst);
}
