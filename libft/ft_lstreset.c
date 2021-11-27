/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 12:02:26 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define ERROR_WHILE_RESETING_TO_SRC 1
#define SUCCESS 0

static int	ft_lstreset_int(t_list *src, t_list *dst,
void *(*copy_content)(void*, void*))
{
	if (!src)
		return (SUCCESS);
	if (!dst)
		return (ERROR_WHILE_RESETING_TO_SRC);
	dst->content = copy_content(src->content, dst->content);
	return (ft_lstreset_int(src->next, dst->next, copy_content));
}

int	ft_lstreset(t_list *head_src, t_list *head_dst,
void *(*copy_content)(void*, void*))
{
	if (!copy_content)
		return (ERROR_WHILE_RESETING_TO_SRC);
	if (!head_src)
		return (SUCCESS);
	if (!head_dst)
		return (ERROR_WHILE_RESETING_TO_SRC);
	return (ft_lstreset_int(head_src, head_dst, copy_content));
}
