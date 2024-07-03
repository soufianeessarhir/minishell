/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:53:28 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/03 05:56:03 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void help(char *line,char **sep_token,int *j,int *i)
{
    if (line[*i] == '>')
    {
        if (line[*i + 1] == '>')
        {
            (*sep_token)[++(*j)] = '>';
            (*i)++;
        }
        (*sep_token)[++(*j)] = '>';
    }
    else if (line[*i] == '<')
    {
        if (line[*i + 1] == '<')
        {
            (*sep_token)[++(*j)] = '<';
            (*i)++;
        }
        (*sep_token)[++(*j)] = '<';
    }
}
void   skip_quoted(char **sep_token,char *line, int *i,int *j)
{
    char c;
    c = line[*i];
    (*sep_token)[++(*j)] = c;
    while (line[++(*i)] != c)
        (*sep_token)[++(*j)] = line[*i];
    (*sep_token)[++(*j)] = c;
    (*i)++;
}
char **ft_tokinize(char *line)
{
    int i;
    int j;
    char *sep_token;

    i = -1;
    j = -1;
   sep_token = malloc (sizeof(char) * (ft_strlen(line) + ft_strlen(line)));
   ft_memset(sep_token, 0, ft_strlen(line) + ft_strlen(line));
   while (line[++i] != '\0')
   {
        if (line[i] == '\"' || line[i] == '\'')
            skip_quoted(&sep_token,line, &i, &j);  
       if (line[i] == '<' || line[i] == '>' || line[i] == '|')
       {
            sep_token[++j] = ' ';
            if (line[i] == '|')
                sep_token[++j] = '|';
            else
                help(line,&sep_token,&j,&i);
          sep_token[++j] = ' ';
       }
        else
            sep_token[++j] = line[i];
   }
   return (ft_split(sep_token, ' '));
}
