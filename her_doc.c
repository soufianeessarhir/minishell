/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/21 19:46:16 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int spaces_included(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return 1;
		i++;
	}
	return 0;
}
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
			if (fd == -1)
		      return;
			tmp->next->value = ft_strjoin("/tmp/",tmp->next->value,l_gc);
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
        }
        if (tmp)
            tmp = tmp->next;
    }
}