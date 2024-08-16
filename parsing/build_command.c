/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:33:31 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 17:33:20 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

static	void	process_token(t_cmd *new, t_token **tmp, t_gc **l_gc)
{
	char	**tmp_p;

	if ((*tmp)->type == 2 && (*tmp)->next && (*tmp)->next->type == 1)
	{
		ft_lstadd_back_redir(&new->rd, new_redir((*tmp)->value, l_gc));
		ft_lstadd_back_redir(&new->rd,
			new_redir((*tmp)->next->value, l_gc));
		*tmp = (*tmp)->next;
	}
	else if ((*tmp)->type != 2)
	{
		if ((*tmp)->is_env == 1 && sp_in_it((*tmp)->value))
		{
			tmp_p = ft_split((*tmp)->value, ' ', l_gc);
		while (tmp_p && *tmp_p) 
		{
			ft_lstadd_back_args(&new->args_lst, new_args(*tmp_p, l_gc));
			tmp_p++; 
		}
		}
		else if ((*tmp)->value)
			ft_lstadd_back_args(&new->args_lst, new_args((*tmp)->value, l_gc));
	}
}

static t_cmd	*process_command(t_token **tmp, t_gc **l_gc)
{
	t_cmd	*new;

	new = new_cmd(l_gc);
	if (!new)
		return (NULL);
	while (*tmp && (*tmp)->type != 3)
	{
		process_token(new, tmp, l_gc);
		*tmp = (*tmp)->next;
	}
	new->args = ft_fill_args(new->args_lst, l_gc);
	return (new);
}

int	init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc)
{
	t_token	*tmp;
	t_cmd	*new;

	tmp = token_lst;
	while (tmp)
	{
		new = process_command(&tmp, l_gc);
		if (!new)
			return (1);
		ft_lstadd_back_cmd(cmd, new);
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}
