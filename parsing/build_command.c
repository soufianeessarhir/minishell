/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:33:31 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/07 00:57:09 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
t_redir *new_redir(char *red_in, t_gc **l_gc) 
{
	t_redir *new;

	new = (t_redir *)ft_malloc(sizeof(t_redir), l_gc);
	new->redio = ft_strdup(red_in, l_gc);
	new->next = NULL;
	return new;
}
t_args *new_args(char *arg, t_gc **l_gc) 
{
	t_args *new;

	new = (t_args *)ft_malloc(sizeof(t_args), l_gc);
	new->arg = ft_strdup(arg, l_gc);
	new->next = NULL;
	return new;
}
void ft_lstadd_back_args(t_args **lst, t_args *new) 
{
	t_args *tmp;

	if (!new) return;
	if (!*lst) {
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_cmd *new_cmd(t_gc **l_gc) 
{
    t_cmd *new;

    new = (t_cmd *)ft_malloc(sizeof(t_cmd), l_gc);
    new->args = NULL;
    new->rd = NULL;
	new->args_lst = NULL;
	new->next = NULL;
	new->prev = NULL;
	return new;
}

char **ft_fill_args(t_args *args_lst, t_gc **l_gc) 
{
	t_args *tmp;
	char **args;
	int i;

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
		args[i] = ft_strdup(clean_str(tmp->arg, l_gc), l_gc);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return args;
}

void ft_lstadd_back_redir(t_redir **lst, t_redir *new)
{
	t_redir *tmp;

	if (!new) return;
	if (!*lst) {
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
	 tmp = tmp->next;
	tmp->next = new;
}
void ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new) {
    t_cmd *tmp;

    if (!new)
	 return;
	if (!*lst) {
		*lst = new;
		return;
	}
	tmp = *lst;
	while (tmp->next)
	tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	
}

int init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc) 
{
    t_token *tmp = token_lst;
    t_cmd *new;
	char **tmp_p;
	t_redir *tmp_redir;
	t_args *tmp_args;

	tmp_redir = NULL;
	tmp_args = NULL;
    while (tmp) 
	{
        new = new_cmd(l_gc);
        if (!new) 
            return 1;
        while (tmp && tmp->type != 3)
		{
            if (tmp->type == 2) 
			{ 
				if (tmp->next && tmp->next->type == 1)
				{
					ft_lstadd_back_redir(&new->rd, new_redir(tmp->value, l_gc));
					ft_lstadd_back_redir(&new->rd, new_redir(clean_str(tmp->next->value, l_gc), l_gc));
					tmp = tmp->next;
				}
            }
			else 
			{
				if (tmp->is_env == 1)
				{
					tmp_p = ft_split(tmp->value, ' ', l_gc);
					while (tmp_p && *tmp_p)
					{
						ft_lstadd_back_args(&new->args_lst, new_args(*tmp_p, l_gc));
						tmp_p++;
					}
				}
				else
					ft_lstadd_back_args(&new->args_lst, new_args(tmp->value, l_gc));
            }
            tmp = tmp->next;
        }
        new->args = ft_fill_args(new->args_lst, l_gc);
        ft_lstadd_back_cmd(cmd, new);
        if (tmp)
		tmp = tmp->next;
    }
	return 0;
}