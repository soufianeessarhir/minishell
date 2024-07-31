/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:53:28 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/31 03:19:15 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *handle_quotes(char *line, int *i, char **sep_token, t_gc **l_gc)
{
    int j;
    char quote;

    j = *i;
    quote = line[*i];
    (*i)++;
    while (line[*i] && line[*i] != quote)
        (*i)++;
    (*i)++;
    *sep_token = ft_strjoin(*sep_token, ft_substr(line, j, *i - j, l_gc), l_gc);
    return *sep_token;
}

char *handle_pipe(char *line, int *i, char **sep_token, t_gc **l_gc)
{
    *sep_token = ft_strjoin(*sep_token, " ", l_gc);
    *sep_token = ft_strjoin(*sep_token, "|", l_gc);
    *sep_token = ft_strjoin(*sep_token, " ", l_gc);
    (*i)++;
	(void)line;
    return *sep_token;
}

char *handle_redirect(char *line, int *i, char **sep_token, t_gc **l_gc)
{
    int len;

    if ((line[*i] == '<' && line[*i + 1] == '<') || (line[*i] == '>' && line[*i + 1] == '>')) {
        len = 2;
    } else {
        len = 1;
    }

    *sep_token = ft_strjoin(*sep_token, " ", l_gc);
    *sep_token = ft_strjoin(*sep_token, ft_substr(line, *i, len, l_gc), l_gc);
    *sep_token = ft_strjoin(*sep_token, " ", l_gc);
    *i = *i + len;

    return *sep_token;
}

char **ft_tokinize(char *line, t_gc **l_gc)
{
    int i;
    int j;
    char *sep_token;

    i = 0;
    sep_token = NULL;
    while (line[i])
    {
        j = i;
        while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>' && line[i] != '\'' && line[i] != '\"')
            i++;
        sep_token = ft_strjoin(sep_token, ft_substr(line, j, i - j, l_gc), l_gc);

        if (line[i] == '\'' || line[i] == '\"')
            sep_token = handle_quotes(line, &i, &sep_token, l_gc);
        else if (line[i] == '|')
            sep_token = handle_pipe(line, &i, &sep_token, l_gc);
        else if (line[i] == '>' || line[i] == '<')
            sep_token = handle_redirect(line, &i, &sep_token, l_gc);
    }
    return (ft_split(sep_token, ' ', l_gc));
}
