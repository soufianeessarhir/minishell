/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/12 19:58:58 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void her_doc_handling(t_token **token_lst, t_gc **l_gc)
{
    t_token *tmp;
    t_token *tmp2;
    t_token *tmp3;
    char *line;
    int i;
    int fd;

    if (!token_lst || !*token_lst)
        return;
    i = 0;
    tmp = *token_lst;
    if (!tmp->next)
        return;
    fd = open(ft_strjoin("/tmp/",tmp->next->value,l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
    while (tmp)
    {
        if (tmp->type == 2 && strncmp(tmp->value, "<<", 2) == 0)
        {
            while (1)
            {
                line = readline(">");
                if (!line || ft_strncmp(line, tmp->next->value, ft_strlen(line)) == 0)
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, "\n", 1);
            }
            close(fd);
            tmp2 = tmp->prev;
            if (tmp->next)
                tmp3 = tmp->next->next;
            else
                tmp3 = NULL;
            if (tmp->value)
                free(tmp->value);
            if (tmp->next && tmp->next->value)
                free(tmp->next->value);
            if (tmp->next)
                free(tmp->next);
            free(tmp);
            if (tmp2)
                tmp2->next = tmp3;
            if (tmp3)
                tmp3->prev = tmp2;
            tmp = tmp3;
        }
        if (tmp)
            tmp = tmp->next;
    }
}