/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:07:47 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/11 17:23:49 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void	ft_lstadd_back(t_gc **lst, t_gc *new)
{
	t_gc	*tmp;

	tmp = *lst;
	if (!*lst && new)
	{
		(*lst) = new;
		return ;
	}
	if (!new || !*lst)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
