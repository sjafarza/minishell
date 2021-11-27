/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdbfind_best_match.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scarboni <scarboni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:38:18 by scarboni          #+#    #+#             */
/*   Updated: 2021/09/16 14:07:22 by scarboni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FOUND 0
#define NOT_FOUND 1
#define ERROR 2

static t_list_double	*ft_lstdbfind_best_match_int(t_list_double *lst,
void *seek, int (*find)(void*, void*))
{
	if (!lst || !find)
		return (NULL);
	if (find(seek, lst->content) == FOUND)
		return (lst);
	return (ft_lstdbfind_best_match_int(lst->next, seek, find));
}

int	ft_lstdbfind_best_match(t_list_double *head_src, t_list_double **found,
void *seek, int (*find)(void*, void*))
{
	t_list_double	*tmp_found;

	if (!head_src)
		return (NOT_FOUND);
	if (!found)
		return (ERROR);
	tmp_found = ft_lstdbfind_best_match_int(head_src, seek, find);
	if (tmp_found)
		*found = tmp_found;
	while (tmp_found && tmp_found->next)
	{
		tmp_found = ft_lstdbfind_best_match_int(tmp_found, seek, find);
		if (tmp_found)
			*found = tmp_found;
	}
	if (!(*found))
		return (NOT_FOUND);
	return (FOUND);
}
