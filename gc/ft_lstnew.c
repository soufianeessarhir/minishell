/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 01:58:15 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/20 14:51:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_gc	*ft_lstnew(void *content)
{
	t_gc	*head;

	if (!content)
		return (NULL);
	head = malloc(sizeof(t_gc));
	if (!head)
		return (NULL);
	head->ptr = content;
	head->next = NULL;
	return (head);
}
