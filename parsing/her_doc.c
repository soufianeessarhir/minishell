/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/09 01:05:50 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_split_here_doc(char *str, int fd,t_gc **l_gc,char *delimiter)
{
	char **args;
	int i;

	args = ft_split(str, '\n',l_gc);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp (args[i],delimiter) == 0)
			return (1);
		write(fd, args[i], ft_strlen(args[i]));
		write(fd, "\n", 1);
		i++;
	}
	return (0);
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
	line = NULL;
    if (!tmp->next)
        return;
    while (tmp)
    {
        if (tmp->type == 2 && strcmp(tmp->value, "<<") == 0)
        {
			if (!tmp->next || (tmp->next->type != 1))
			   break;
    			fd = open(ft_strjoin("/tmp/heredoc",clean_str(tmp->next->value,l_gc),l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (fd == -1)
		      return;
			if (isatty(0))
			{
				g_a.stphedorc_insgin = 1;
				line = readline(">");
			}
            while (isatty(0))
            {
                if (!line || ft_split_here_doc(line, fd,l_gc,clean_str(tmp->next->value,l_gc)))
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, "\n", 1);
				free(line);
				line = NULL;
                line = readline(">");
            }
			tmp->next->value = ft_strjoin("/tmp/heredoc",clean_str(tmp->next->value,l_gc),l_gc);
            close(fd);
        }
        if (tmp)
            tmp = tmp->next;
    }
}
