/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 02:22:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 17:30:46 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*new_redir(char *red_in, t_gc **l_gc)
{
	t_redir	*new;

	new = (t_redir *)ft_malloc(sizeof(t_redir), l_gc);
	new->redio = red_in;
	new->next = NULL;
	return (new);
}

t_args	*new_args(char *arg, t_gc **l_gc)
{
	t_args	*new;

	new = (t_args *)ft_malloc(sizeof(t_args), l_gc);
	new->arg = arg;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_args(t_args **lst, t_args *new)
{
	t_args	*tmp;

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

t_cmd	*new_cmd(t_gc **l_gc)
{
	t_cmd	*new;

	new = (t_cmd *)ft_malloc(sizeof(t_cmd), l_gc);
	new->args = NULL;
	new->rd = NULL;
	new->args_lst = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

char	**ft_fill_args(t_args *args_lst, t_gc **l_gc)
{
	t_args	*tmp;
	char	**args;
	int		i;

	i = 0;
	tmp = args_lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	args = (char **)ft_malloc(sizeof(char *) * (i + 1), l_gc);
	i = 0;
	tmp = args_lst;
	while (tmp)
	{
		args[i] = tmp->arg;
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
