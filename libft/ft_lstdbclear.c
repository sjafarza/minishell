/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/08/14 19:10:18 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_lstdbclear_int(t_list_double *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	ft_lstdbclear_int(lst->next, del);
	if (lst->content)
		(*del)(lst->content);
	free(lst);
}

void	ft_lstdbclear(t_list_double **lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	ft_lstdbclear_int(*lst, del);
	*lst = NULL;
}
