/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:10:29 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ERROR_WHILE_COPYING 1
#define SUCCESS 0

static int	ft_lstdbcpy_int(t_list_double *src, t_list_double **dst,
void *(*copy_create_content)(void*))
{
	if (!src)
		return (SUCCESS);
	if (copy_create_content)
		*dst = ft_lstdbnew(copy_create_content(src->content));
	else
		*dst = ft_lstdbnew(src->content);
	if (!*dst)
		return (ERROR_WHILE_COPYING);
	return (ft_lstdbcpy_int(src->next, &((*dst)->next), copy_create_content));
}

static void	ft_lstdbcpy_int_for_prev(t_list_double *prev,
t_list_double *current)
{
	if (!current)
		return ;
	current->prev = prev;
	ft_lstdbcpy_int_for_prev(current, current->next);
}

int	ft_lstdbcpy(t_list_double *head_src, t_list_double **head_dst,
void *(*copy_create_content)(void*))
{
	if (!head_src)
		return (ERROR_WHILE_COPYING);
	if (ft_lstdbcpy_int(head_src, head_dst, copy_create_content) != SUCCESS)
		return (ERROR_WHILE_COPYING);
	ft_lstdbcpy_int_for_prev(NULL, (*head_dst));
	return (SUCCESS);
}
