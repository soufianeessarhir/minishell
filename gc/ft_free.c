/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 01:08:46 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/29 09:07:38 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

void    ft_free(t_gc **lst)
{
    t_gc  *tmp;

    if (!*lst)
        return ;
    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->ptr);
        free(*lst);
        *lst = tmp;
    }
}

