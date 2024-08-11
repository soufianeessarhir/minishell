/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:59:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/11 02:18:46 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	token_type(char *str)
{
	if (str[0] == '|')
		return (3);
	if (str[0] == '>' || str[0] == '<')
		return (2);
	return (1);
}

void	init_graph(int graph[4][3])
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

int	syntax_error(t_token **token, t_gc **l_gc)
{
	int		graph[4][3];
	int		state;
	t_token	*tmp;

	state = 0;
	init_graph(graph);
	tmp = *token;
	while (tmp)
	{
		state = graph[state][tmp->type - 1];
		if (state == -1)
		{
			ft_putstr_fd(ft_strjoin(ft_strjoin("syntax error near unexpected token `", tmp->value, l_gc),"\'\n",l_gc), 2);
			break ;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL && state == 1)
		return (her_doc_handling(token, l_gc), 0);
	else if (state != 1 && tmp != NULL)
	{
		if (tmp->prev != NULL)
			tmp->prev->next = NULL;
		else
			*token = NULL;
		return (her_doc_handling(token, l_gc), 1);
		
	}
	return (her_doc_handling(token, l_gc),
		ft_putstr_fd("syntax error near unexpected token `newline\' \n",2), 1);
}
