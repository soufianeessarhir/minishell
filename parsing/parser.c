/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 05:59:54 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/23 17:23:40 by sessarhi         ###   ########.fr       */
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

int	process_tokens(t_token **tmp, int graph[4][3], t_gc **l_gc)
{
	int	state ;

	state = 0;
	while (*tmp)
	{
		state = graph[state][(*tmp)->type - 1];
		if (state == -1)
		{
			ft_putstr_fd(ft_strjoin(
					ft_strjoin
					("minishell: syntax error near unexpected token `",
						(*tmp)->value, l_gc), "\'\n", l_gc), 2);
			return (-1);
		}
		(*tmp) = (*tmp)->next;
	}
	return (state);
}

int	syntax_error(t_token **token, t_gc **l_gc, t_env *env_lst)
{
	int		graph[4][3];
	int		state;
	t_token	*tmp;

	init_graph(graph);
	tmp = *token;
	state = process_tokens(&tmp, graph, l_gc);
	if (tmp == NULL && state == 1)
		return (her_doc_handling(token, l_gc, env_lst), 0);
	else if (state != 1 && tmp != NULL)
	{
		if (tmp->prev != NULL)
			tmp->prev->next = NULL;
		else
			*token = NULL;
		return (her_doc_handling(token, l_gc, env_lst), 1);
	}
	return (her_doc_handling(token, l_gc, env_lst),
		ft_putstr_fd
		("minishell: syntax error near unexpected token `newline\' \n", 2), 1);
}

int	parsing_part(t_help *help, t_env **env_lst, t_gc **l_gc, t_cmd **cmd)
{
	t_token	*token_lst;

	token_lst = NULL;
	if (sp_uq_handling(help->line))
		return (1);
	ft_tokinize(help->line, &token_lst, l_gc);
	if (syntax_error(&token_lst, l_gc, *env_lst))
		return (ft_export_status(258, help->env, l_gc, help->lst), 1);
	her_doc_handling(&token_lst, l_gc, *env_lst);
	env_handling(&token_lst, *env_lst, l_gc);
	init_cmd(cmd, token_lst, l_gc);
	if (open_redirection(cmd, l_gc))
		return (ft_export_status(1, help->env, l_gc, help->lst), 1);
	return (0);
}
