/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:58:22 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/28 07:10:59 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_red_in(t_cmd *tmp, char **args, t_gc **l_gc)
{
    int i = 0;
    args = ft_split(tmp->red_in, ' ', l_gc);
    if (args[0] != NULL)
    {
        while (args[i])
        {
            if (args[i] && (ft_strcmp(args[i], "<<") == 0 || ft_strcmp(args[i], "<") == 0))
            {
                if ( args[i + 1] == NULL || args[i + 1][0] == '<' || args[i + 1][0] == '>')
                    return(printf("ambiguous redirect\n"),1);
                else if (args[i + 1] && args[i + 1][0] == '\0')
                    return(printf("minishell: %s: No such file or directory\n", args[i + 1]),1);
                else if (args[i + 1] && access(args[i + 1], R_OK) == -1)
                    return(printf("minishell: %s: Permission denied\n", args[i + 1]),1);
                tmp->red_in_fd = open(args[i + 1], O_RDONLY);
                if (tmp->red_in_fd == -1)
                    return 1;
                i+=2;
            }
        }
    }
	return 0;
}

int handle_append_redirection(t_cmd *tmp, char **args, int i)
{
    if (args[i + 1] == NULL || args[i + 1][0] == '<' || args[i + 1][0] == '>')
        return(printf("ambiguous redirect\n"),1);
	else if (args[i + 1] && args[i + 1][0] == '\0')
		return(printf("minishell: %s: No such file or directory\n", args[i + 1]),1);
    if (args[i + 1] && access(args[i + 1], F_OK) == 0 && access(args[i + 1], W_OK) == -1)
        return(printf("minishell: %s: Permission denied\n", args[i + 1]),1);   
    tmp->red_out_fd = open(args[i + 1], O_APPEND | O_CREAT | O_RDWR, 0644);
    if (tmp->red_out_fd == -1)
        return 1;
	return 0;
}

int handle_overwrite_redirection(t_cmd *tmp, char **args, int i)
{
    if (args[i + 1] && access(args[i + 1], F_OK) == 0 && access(args[i + 1], W_OK) == -1)
        return(printf("minishell: %s: Permission denied\n", args[i + 1]),1);
    tmp->red_out_fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (tmp->red_out_fd == -1)
        return 1;
	return 0;
}

int handle_red_out(t_cmd *tmp, char **args, t_gc **l_gc)
{
    int i = 0;
    args = ft_split(tmp->red_out, ' ', l_gc);
    if (args[0] != NULL)
    {
        while (args[i])
        {
            if (args[i] && ft_strcmp(args[i], ">>") == 0)
            {
				if (args[i + 1] == NULL || ft_strcmp(args[i + 1], ">>") == 0 || ft_strcmp(args[i + 1], ">") == 0 || ft_strcmp(args[i + 1], "<<") == 0 || ft_strcmp(args[i + 1], "<") == 0)
        			return(printf("ambiguous redirect\n"),1);
				else if (args[i + 1][0] == '\0' && args[i + 1])
					return(printf("minishell: %s: No such file or directory\n", args[i + 1]),1);
				if ( handle_append_redirection(tmp, args, i))
               		return 1;
                i+=2;
            }
            else if (args[i] && ft_strcmp(args[i], ">") == 0)
            {
				if (args[i + 1] == NULL || ft_strcmp(args[i + 1], ">>") == 0 || ft_strcmp(args[i + 1], ">") == 0 || ft_strcmp(args[i + 1], "<<") == 0 || ft_strcmp(args[i + 1], "<") == 0)
       				 return(printf("ambiguous redirect\n"),1);
				else if (args[i + 1][0] == '\0' && args[i + 1])
					return(printf("minishell: %s: No such file or directory\n", args[i + 1]),1);
                handle_overwrite_redirection(tmp, args, i);
                i+=2;
            }
			else
			   i++;
        }
    }
	return (0);
}

int  open_redirection(t_cmd **cmd , t_gc **l_gc)
{
    t_cmd *tmp;
    char **args;

    tmp = *cmd;
	args = NULL;
    while (tmp)
    {
        if (tmp->red_in && tmp->red_in[0] != '\0')
			if (handle_red_in(tmp, args, l_gc))
	            return 1;
        if (tmp->red_out && tmp->red_out[0] != '\0')
			if (handle_red_out(tmp, args, l_gc))
				return 1;   
        tmp = tmp->next;
    }
	return 0;
}