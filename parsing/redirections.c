/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:58:22 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 05:14:48 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_path(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i -1] != '.')
			return 1;
		i++;
	}
	return 0;
}

int handle_redirections(t_cmd *tmp, t_gc **l_gc)
{
    while (tmp->rd)
    {
        if (tmp->rd->redio && (ft_strcmp(tmp->rd->redio, ">") == 0 || ft_strcmp(tmp->rd->redio, ">>") == 0))
        {
            if (handle_red_out(tmp, l_gc, tmp->rd))
            {
                tmp->exit_status = 1;
                return 1;
            }
        }
        else if (tmp->rd->redio && (ft_strcmp(tmp->rd->redio, "<") == 0 || ft_strcmp(tmp->rd->redio, "<<") == 0))
        {
            if (handle_red_in(tmp, l_gc, tmp->rd))
            {
                tmp->exit_status = 1;
                return 1;
            }
        }
        if (tmp->rd->next)
            tmp->rd = tmp->rd->next->next;
        else
            break;
    }
    return 0;
}

int open_redirection(t_cmd **cmd, t_gc **l_gc)
{
    t_cmd *tmp;

    tmp = *cmd;
    while (tmp)
    {
        tmp->red_in_fd = 0;
        tmp->red_out_fd = 1;
        tmp->exit_status = 0;
        if (tmp->rd)
        {
            if (handle_redirections(tmp, l_gc))
            {
                if (!tmp->next)
                    return 1;
            }
        }
        tmp = tmp->next;
    }
    return 0;
}
