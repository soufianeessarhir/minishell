/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/18 02:59:26 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void her_doc_handling(t_token **token_lst, t_gc **l_gc)
{
    t_token *tmp;
    char *line;
    int i;
    int fd;

    if (!token_lst || !*token_lst)
        return;
    i = 0;
    tmp = *token_lst;
    if (!tmp->next)
        return;
    while (tmp)
    {
        if (tmp->type == 2 && strcmp(tmp->value, "<<") == 0)
        {
    		fd = open(ft_strjoin("/tmp/",tmp->next->value,l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
            while (1)
            {
                line = readline(">");
                if (!line || ft_strcmp(line, tmp->next->value) == 0)
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, "\n", 1);
				free(line);
            }
            close(fd);
           tmp->next->value = ft_strjoin("/tmp/",tmp->next->value,l_gc);
        }
        if (tmp)
            tmp = tmp->next;
    }
}