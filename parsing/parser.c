/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:59:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/24 06:14:58 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    token_type(char *str)
{
    if (str[0] == '|')
        return (3);
    if (str[0] == '>' || str[0] == '<')
        return (2);
    return (1);
}
t_token *init_token(char **str,t_token **token,t_gc **l_gc)
{
    int i;
    t_token *tmp;
    

    i = 0;
    while (str[i] != NULL)
    {
        tmp = ft_dll_lstnew(str[i],token_type(str[i]),l_gc);
        ft_dll_lstadd_back(token,tmp);
        i++;
    }
    return (*token);
    
}

void  init_graph(int graph[4][3])
{
    graph[0][0] = 1;
    graph[0][1] = 2;
    graph[0][2] = -1;
    graph[1][0] = 1;
    graph[1][1] = 2;
    graph[1][2] = 3;
    graph[2][0] = 1;
    graph[2][1] = -1;
    graph[2][2] = -1;
    graph[3][0] = 1;
    graph[3][1] = 2;
    graph[3][2] = -1;
}

int syntax_error(char **args,t_token **token,t_gc **l_gc)
{
    int graph[4][3];
    int state;
    t_token *tmp;
    
    state = 0;
    init_graph(graph);
    init_token(args,token, l_gc);
    tmp = *token;
    while (tmp)
    {
        state = graph[state][tmp->type - 1];
        if (state == -1)
            {
				printf("syntax error near unexpected token `%s'\n", tmp->value);
				break;
			}
        tmp = tmp->next;
    }
    if (tmp == NULL && state == 1)
        return (her_doc_handling(token, l_gc),0);	
	else if (state != 1 && tmp != NULL)
		return (tmp = NULL, her_doc_handling(token, l_gc), 1);
	return (her_doc_handling(token, l_gc), printf("syntax error near unexpected token `newline'\n"), 1);
}
