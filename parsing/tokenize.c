/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:53:28 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/06 01:22:06 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void handle_word(char *line, int *i,t_token **token_lst, t_gc **l_gc)
{
    int j;
    char quote;

	j = *i;
    while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && line[*i] != '>' && line[*i] != '<' && line[*i] != '|')
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[*i];
			(*i)++;
			while (line[*i] && line[*i] != quote)
				(*i)++;
			(*i)++;
		}
		else
		(*i)++;
	}
	ft_dll_lstadd_back(token_lst, ft_dll_lstnew(ft_substr(line, j, *i - j, l_gc), 1, l_gc));
	
}

void handle_pipe(int *i,t_token **token_lst, t_gc **l_gc)
{
	ft_dll_lstadd_back(token_lst, ft_dll_lstnew("|", 3, l_gc));
    (*i)++;
}

void handle_redirect(char *line,int *i,t_token **token_lst, t_gc **l_gc)
{
    int len;

    if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>' && line[*i + 1] == '>')) 
        len = 2;
	 else
        len = 1;
    ft_dll_lstadd_back(token_lst, ft_dll_lstnew(ft_substr(line, *i, len, l_gc), 2, l_gc));
    *i = *i + len;
}

void ft_tokinize(char *line,t_token **token_lst, t_gc **l_gc)
{
    int i;

    i = 0;
    while (line[i])
    {
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
        if (line[i] == '|')
			handle_pipe(&i, token_lst, l_gc);
        else if (line[i] == '>' || line[i] == '<')
            handle_redirect(line, &i, token_lst, l_gc);
		else
			handle_word(line, &i, token_lst, l_gc);
    }
}
