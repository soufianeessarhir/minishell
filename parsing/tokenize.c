/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:53:28 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/14 18:04:30 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_tokinize(char *line,t_gc **l_gc)
{
    int i;
    int j;
    char *sep_token;
	char quote;

    i = 0;
	j = 0;
    sep_token = NULL;
   while (line[i])
	{
			j = i;
			while (line[i] && line[i] != '|' && line[i] != '<' && line[i] != '>')
				i++;
			sep_token = ft_strjoin(sep_token, ft_substr(line, j, i - j, l_gc), l_gc);
		
		if (line[i] == '\'' || line[i] == '\"')
		{
			j = i;
			quote = line[i];
			i++;
			while (line[i] && line[i] != quote)
				i++;
			i++;
	       sep_token = ft_strjoin(sep_token,ft_substr(line, j, i - j, l_gc), l_gc);

		}
		else if (line[i] == '|')
		{
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			sep_token = ft_strjoin(sep_token, "|", l_gc);
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			i++;
		}
		else if ((line[i] == '<' && line[i + 1] == '<') || (line[i] == '>' && line[i + 1] == '>'))
		{
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			sep_token = ft_strjoin(sep_token, ft_substr(line, i, 2, l_gc), l_gc);
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			i += 2;
		}
		else if (line[i] == '>' || line[i] == '<')
		{
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			sep_token = ft_strjoin(sep_token, ft_substr(line, i, 1, l_gc), l_gc);
			sep_token = ft_strjoin(sep_token, " ", l_gc);
			i++;
		}
	
		
	
	}
    return (ft_split(sep_token, ' ', l_gc));
}
