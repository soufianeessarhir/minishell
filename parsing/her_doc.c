/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 01:15:16 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_heredoc
{
	char *line;
	int fd;
	char *delimiter;
	
} t_heredoc;

int ft_split_here_doc(t_heredoc herdoc,t_gc **l_gc, t_env *env_lst)
{
	char **args;
	int i;

	args = ft_split(herdoc.line, '\n',l_gc);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp (args[i],clean_str(herdoc.delimiter,l_gc)) == 0)
			return (1);
		if (is_dollar(args[i]) && herdoc.delimiter[0] != '\'' && herdoc.delimiter[0] != '\"')
			args[i] = helper(args[i], l_gc, env_lst, -1);
		write(herdoc.fd, args[i], ft_strlen(args[i]));
		write(herdoc.fd, "\n", 1);
		i++;
	}
	return (0);
}

void her_doc_handling(t_token **token_lst, t_gc **l_gc, t_env *env_lst)
{
    t_token *tmp;
    t_heredoc heredoc;

    if (!token_lst || !*token_lst)
        return;
    tmp = *token_lst;
	heredoc.line = NULL;
    while (tmp)
    {
        if (tmp->type == 2 && strcmp(tmp->value, "<<") == 0)
        {
			if (!tmp->next || (tmp->next->type != 1))
			   break;
    			heredoc.fd = open(ft_strjoin("/tmp/heredoc",clean_str(tmp->next->value,l_gc),l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (heredoc.fd == -1)
		      return;
			if (isatty(0))
				g_a.stphedorc_insgin = 1;
			heredoc.line = readline(">");
            while (isatty(0))
            {
					heredoc.delimiter = tmp->next->value;
                if (!heredoc.line || ft_split_here_doc(heredoc,l_gc,env_lst))
                    break;
				free(heredoc.line);
				heredoc.line = NULL;
                heredoc.line= readline(">");
            }
			tmp->next->value = ft_strjoin("/tmp/heredoc",clean_str(tmp->next->value,l_gc),l_gc);
            close(heredoc.fd);
        }
        if (tmp)
            tmp = tmp->next;
    }
}
