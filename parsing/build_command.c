/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 22:33:31 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/03 05:08:31 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd *new_cmd(t_gc **l_gc) 
{
    t_cmd *new;

    new = (t_cmd *)ft_malloc(sizeof(t_cmd), l_gc);
    new->cmd = ft_strdup("", l_gc);
	new->red_in = ft_strdup("", l_gc);
	new->red_out = ft_strdup("", l_gc);
	new->args = NULL;
	new->next = NULL;
	return new;
}

char **ft_rem_quotes(char **args, t_gc **l_gc)
{
	int i ;
	
	i = 0;
	if (!args)
		return NULL;
	while (args[i])
	{
		args[i] = clean_str(args[i], l_gc);
		i++;
	}
	return args;
}
void ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new) {
    t_cmd *tmp;

    if (!new) return;
    if (!*lst) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next) tmp = tmp->next;
    tmp->next = new;
}

int init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc) {
    t_token *tmp = token_lst;
    t_cmd *new;
	char **tmp_args;

    while (tmp) 
	{
        new = new_cmd(l_gc);
        if (!new) 
            return 1;
        while (tmp && tmp->type != 3)
		{
            if (tmp->type == 2) 
			{ 
	            if (ft_strcmp(tmp->value, ">") == 0 || ft_strcmp(tmp->value, ">>") == 0) 
				{
					new->red_out = ft_strjoin(new->red_out, tmp->value, l_gc);
					new->red_out = ft_strjoin(new->red_out, " ", l_gc);
					if (tmp->next && tmp->next->type == 1) 
					{
						if (ft_strcmp(clean_str(tmp->next->value , l_gc), "") == 0)
							return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", clean_str(tmp->next->value,l_gc), l_gc), "No such file or directory\n", l_gc),2),1);
						new->red_out = ft_strjoin(new->red_out, clean_str(tmp->next->value , l_gc), l_gc);
						new->red_out = ft_strjoin(new->red_out, " ", l_gc);
						tmp = tmp->next;
					}
				} 
				else if (ft_strcmp(tmp->value, "<") == 0 || ft_strcmp(tmp->value, "<<") == 0) 
				{
					new->red_in = ft_strjoin(new->red_in, tmp->value, l_gc);
					new->red_in = ft_strjoin(new->red_in, " ", l_gc);
					if (tmp->next && tmp->next->type == 1) 
					{
						if (ft_strcmp(clean_str(tmp->next->value , l_gc), "") == 0)
							return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", clean_str(tmp->next->value,l_gc), l_gc), "No such file or directory\n", l_gc),2),1);
						new->red_in = ft_strjoin(new->red_in, clean_str(tmp->next->value,l_gc), l_gc);
						new->red_in = ft_strjoin(new->red_in, " ", l_gc);
						tmp = tmp->next;
					}
				}
            }
			else 
			{
				if (tmp->is_env == 1)
				{
					tmp_args = ft_split(tmp->value, ' ', l_gc);
					while (tmp_args && *tmp_args)
					{
						new->cmd = ft_strjoin(new->cmd, *tmp_args, l_gc);
						new->cmd = ft_strjoin(new->cmd, " ", l_gc);
						tmp_args++;
					}
				}
				else
				{
	                new->cmd = ft_strjoin(new->cmd,tmp->value, l_gc);
	                new->cmd = ft_strjoin(new->cmd, " ", l_gc);
				}
            }
            tmp = tmp->next;
        }
		new->args = ft_split(new->cmd, ' ', l_gc);
		new->args = ft_rem_quotes(new->args, l_gc);
        ft_lstadd_back_cmd(cmd, new);
        if (tmp)
		tmp = tmp->next;
    }
	return 0;
}