/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 01:08:46 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/13 00:35:35 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void ft_free(t_gc **lst)
{
    t_gc *tmp;

    while (*lst)
    {
        tmp = *lst;
        *lst = (*lst)->next;
        free(tmp->ptr);
        tmp->ptr = NULL;
        free(tmp);
        tmp = NULL;
    }
}

