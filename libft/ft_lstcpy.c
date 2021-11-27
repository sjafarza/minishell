/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 12:00:01 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ERROR_WHILE_COPYING 1
#define SUCCESS 0

static int	ft_lstcpy_int(t_list *src, t_list **dst,
void *(*copy_create_content)(void*))
{
	if (!src)
		return (SUCCESS);
	if (copy_create_content)
		*dst = ft_lstnew(copy_create_content(src->content));
	else
		*dst = ft_lstnew(src->content);
	if (!*dst)
		return (ERROR_WHILE_COPYING);
	return (ft_lstcpy_int(src->next, &((*dst)->next), copy_create_content));
}

int	ft_lstcpy(t_list *head_src, t_list **head_dst,
void *(*copy_create_content)(void*))
{
	if (!head_src)
		return (ERROR_WHILE_COPYING);
	return (ft_lstcpy_int(head_src, head_dst, copy_create_content));
}
