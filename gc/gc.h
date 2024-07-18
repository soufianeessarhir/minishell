/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:53:42 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/11 04:22:34 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# ifndef GC_H
# define GC_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_gc
{
 void *ptr;
    struct s_gc *next;
}				t_gc;
void    ft_lstadd_front(t_gc **lst, t_gc *new);
void    ft_lstadd_back(t_gc **lst, t_gc *new);
void    ft_lstclear(t_gc **lst, void (*del)(void *));
t_gc  *ft_lstnew(void *content);
void    ft_lstdelone(t_gc *lst, void (*del)(void *));
int     ft_lstsize(t_gc *lst);
t_gc  *ft_lstlast(t_gc *lst);
void    ft_free(t_gc **lst);
void    *ft_malloc(size_t size, t_gc **lst);

#endif