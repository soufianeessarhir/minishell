/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:50:15 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 06:15:32 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	*ft_malloc(size_t size, t_gc **lst)
{
	t_gc	*new;

	new = ft_lstnew(malloc(size));
	if (!new)
		return (NULL);
	ft_lstadd_back(lst, new);
	return (new->ptr);
}
