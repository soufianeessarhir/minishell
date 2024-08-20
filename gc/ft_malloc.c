/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:50:15 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/20 16:15:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*ft_malloc(size_t size, t_gc **lst)
{
	t_gc		*new;
	t_gc		*fail_node;
	static t_gc	*gc_fail;
	void		*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (ft_free(&gc_fail),
			exit(printf("Error: malloc failed\n")), NULL);
	new = ft_lstnew(ptr);
	if (!new)
		return (ft_free(&gc_fail),
			exit(printf("Error: node creation failed\n")), NULL);
	ft_lstadd_back(lst, new);
	fail_node = ft_lstnew(ptr);
	if (!fail_node)
		return (ft_free(&gc_fail),
			exit(printf("Error: node creation failed\n")), NULL);
	else
		ft_lstadd_back(&gc_fail, fail_node);
	return (ptr);
}
