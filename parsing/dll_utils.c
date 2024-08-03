/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:38:06 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/03 03:22:17 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *ft_dll_lstnew(char *content, int type, t_gc **l_gc)
{
    t_token *new;

    new = ft_malloc(sizeof(t_token), l_gc);
    if (!new)
        return (NULL);
    new->value = content;
    new->type = type;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    ft_dll_lstadd_front(t_token **lst, t_token *new)
{
    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    new->next = *lst;
    (*lst)->prev = new;
    *lst = new;
}

void    ft_dll_lstadd_back(t_token **lst, t_token *new)
{
    t_token *tmp;

    if (!new)
        return ;
    if (!*lst)
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}

void    ft_dll_lstclear(t_token **lst)
{
    t_token *tmp;

    if (!*lst)
        return ;
    while (*lst)
    {
        tmp = *lst;
        *lst = (*lst)->next;
        free(tmp);
    }
}
int     ft_dll_lstsize(t_token *lst)
{
    int i;

    i = 0;
    while (lst)
    {
        i++;
        lst = lst->next;
    }
    return (i);
}

