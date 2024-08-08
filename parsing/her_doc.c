/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/08 03:37:00 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	line = NULL;
    if (!tmp->next)
        return;
    while (tmp)
    {
        if (tmp->type == 2 && strcmp(tmp->value, "<<") == 0)
        {
			if (!tmp->next || !(tmp->next->type == 1))
			   break;
			 if (ft_strcmp(clean_str(tmp->next->value,l_gc), "") ==  0)
			    fd = open("/tmp/heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
			else
    			fd = open(ft_strjoin("/tmp/",clean_str(tmp->next->value,l_gc),l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
		      return;
			if (isatty(0))
			{
				g_a.stphedorc_insgin = 1;
				line = readline(">");
			}
            while (isatty(0))
            {
                if (!line || ft_strcmp(line,clean_str(tmp->next->value,l_gc)) == 0)
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, "\n", 1);
				free(line);
                line = readline(">");
            }
			tmp->next->value = ft_strjoin("/tmp/",tmp->next->value,l_gc);
            close(fd);
        }
        if (tmp)
            tmp = tmp->next;
    }
}
