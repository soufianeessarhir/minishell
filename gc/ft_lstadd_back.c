/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:07:47 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/20 18:24:33 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void ft_lstadd_back(t_gc **lst, t_gc *new) 
{
    t_gc *tmp;

	if (!*lst && !new)
		return;
    if (!new)
        return;
    if (!*lst) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
