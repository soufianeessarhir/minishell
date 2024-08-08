/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:58:22 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/08 03:59:06 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void deleteCmdNode(t_cmd** head_ref, t_cmd* del) 
{
    if (*head_ref == NULL || del == NULL)
        return;
    if (*head_ref == del)
        *head_ref = del->next;
    if (del->next != NULL)
        del->next->prev = del->prev;
    if (del->prev != NULL)
        del->prev->next = del->next;
}
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
static int is_directory(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}
int handle_red_in(t_cmd *tmp, t_gc **l_gc, t_redir *rd) 
{
	if (rd->next && !rd->next->redio)
		return (1);
	if (rd->next && is_directory(rd->next->redio))
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", rd->next->redio, l_gc), ": Is a directory\n", l_gc),2),1);
	if(rd->next && access(rd->next->redio, F_OK) == -1)
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", rd->next->redio, l_gc), ": No such file or directory\n", l_gc),2),1);
	if (tmp->prev && tmp->prev->red_in_fd != 0)
	{
		close(tmp->prev->red_in_fd);	
	}
	tmp->red_in_fd = open(rd->next->redio, O_RDONLY);
	if (tmp->red_in_fd == -1)
		return 1;
	return 0;
}

int handle_append_redirection(t_cmd *tmp,char *redout, t_gc **l_gc)
{
	if (!redout)
		return (1);
	if (redout && is_directory(redout))
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": Is a directory\n", l_gc),2),1);
	if((redout && access(redout, F_OK) == -1 && is_path(redout)) || ft_strcmp (redout, "") == 0)
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": No such file or directory\n", l_gc),2),1);
    if (redout && access(redout, F_OK) == 0 && access(redout, W_OK) == -1)
        return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": Permission denied\n", l_gc),2),1);   
	if (tmp->prev && tmp->prev->red_out_fd != 1)
	close(tmp->prev->red_out_fd);
    tmp->red_out_fd = open(redout, O_APPEND | O_CREAT | O_RDWR, 0644);
    if (tmp->red_out_fd == -1)
        return 1;
	return 0;
}

int handle_overwrite_redirection(t_cmd *tmp,char *redout, t_gc **l_gc)
{
	if (!redout)
		return (1);
	if (redout && is_directory(redout))
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": Is a directory\n", l_gc),2),1);
	if((redout && access(redout, F_OK) == -1 && is_path(redout)) || ft_strcmp (redout, "") == 0)
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": No such file or directory\n", l_gc),2),1);
	if (redout && access(redout, F_OK) == 0 && access(redout, W_OK) == -1)
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", redout, l_gc), ": Permission denied\n", l_gc),2),1);
	if (tmp->prev && tmp->red_out_fd != 1)
	close(tmp->red_out_fd);
	tmp->red_out_fd = open(redout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp->red_out_fd == -1)
		return 1;
	return 0;
}

int handle_red_out(t_cmd *tmp, t_gc **l_gc,t_redir *rd)
{
     if (rd->redio && ft_strcmp(rd->redio, ">") == 0)
	{
		if (rd->next &&handle_overwrite_redirection(tmp, rd->next->redio, l_gc) )
			return 1;
	}
	else if (rd->redio && ft_strcmp(rd->redio, ">>") == 0)
	{
		if ( rd->next && handle_append_redirection(tmp,rd->next->redio, l_gc) )
			return 1;
	}
	return 0;
}
void open_redirection(t_cmd **cmd , t_gc **l_gc,t_help *help)
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
            while (tmp->rd)
            {
                if (tmp->rd->redio && (ft_strcmp(tmp->rd->redio, ">") == 0 || ft_strcmp(tmp->rd->redio, ">>") == 0))
                {
                    if (handle_red_out(tmp, l_gc, tmp->rd))
                    {
						tmp->exit_status = 1;
                        export_status(1, help->env, l_gc, help->lst);
                        break;
                    }
                }
                else if (tmp->rd->redio && (ft_strcmp(tmp->rd->redio, "<") == 0 || ft_strcmp(tmp->rd->redio, "<<") == 0))
                {
                    if (handle_red_in(tmp, l_gc, tmp->rd))
                    {
                        tmp->exit_status = 1;
                        export_status(1, help->env, l_gc, help->lst);
                        break;
                    }
                }
				if (tmp->rd->next)
    				tmp->rd = tmp->rd->next->next;
            }
        }
        tmp = tmp->next;
    }
}
