/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 06:17:07 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/29 08:58:53 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	*ft_lstmap(t_gc *lst, void *(*f)(void *), void (*del)(void *))
{
	t_gc	*frst;
	t_gc	*s;
	void	*content;

	s = NULL;
	if (!lst || !del)
		return (NULL);
	while (lst)
	{
		content = f(lst->ptr);
		frst = ft_lstnew(content);
		if (!frst)
		{
			del(content);
			if (s)
				ft_lstclear(&s, del);
			return (NULL);
		}
		lst = lst->next;
		ft_lstadd_back(&s, frst);
	}
	return (s);
}
