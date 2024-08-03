/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 03:58:22 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/03 05:09:34 by sessarhi         ###   ########.fr       */
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
int not_directory(char *path)
{
	struct stat path_stat;
	stat(path, &path_stat);
	return S_ISDIR(path_stat.st_mode);
}
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
			   if (args[i + 1] && access(args[i + 1], F_OK) == -1)
					return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": No such file or directory\n", l_gc),2),1);
               if (args[i + 1] && access(args[i + 1], F_OK) == 0 && access(args[i + 1], R_OK) == -1)
                    return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": Permission denied\n", l_gc),2),1);
                tmp->red_in_fd = open(args[i + 1], O_RDONLY);
                if (tmp->red_in_fd == -1)
                    return 1;
                i+=2;
            }
        }
    }
	return 0;
}

int handle_append_redirection(t_cmd *tmp, char **args, int i, t_gc **l_gc)
{
	if(args[i + 1] && access(args[i + 1], F_OK) == -1 && is_path(args[i + 1]))
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": No such file or directory\n", l_gc),2),1);
    if (args[i + 1] && access(args[i + 1], F_OK) == 0 && access(args[i + 1], W_OK) == -1)
        return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": Permission denied\n", l_gc),2),1);   
    tmp->red_out_fd = open(args[i + 1], O_APPEND | O_CREAT | O_RDWR, 0644);
    if (tmp->red_out_fd == -1)
        return 1;
	return 0;
}

int handle_overwrite_redirection(t_cmd *tmp, char **args, int i, t_gc **l_gc)
{
	if(args[i + 1] && access(args[i + 1], F_OK) == -1 && is_path(args[i + 1]))
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": No such file or directory\n", l_gc),2),1);
	if (args[i + 1] && access(args[i + 1], F_OK) == 0 && access(args[i + 1], W_OK) == -1)
		return(ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", args[i + 1], l_gc), ": Permission denied\n", l_gc),2),1);
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
				if ( handle_append_redirection(tmp, args, i, l_gc))
               		return 1;
                i+=2;
            }
            else if (args[i] && ft_strcmp(args[i], ">") == 0)
            {
				if (handle_overwrite_redirection(tmp, args, i, l_gc))
			   		return 1;
                i+=2;
            }
			else
			   i++;
        }
    }
	return (0);
}

void  open_redirection(t_cmd **cmd , t_gc **l_gc)
{
    t_cmd *tmp;
    char **args;

    tmp = *cmd;
	args = NULL;
    while (tmp)
    {
        if (tmp->red_in && tmp->red_in[0] != '\0')
			handle_red_in(tmp, args, l_gc);
        if (tmp->red_out && tmp->red_out[0] != '\0')
			handle_red_out(tmp, args, l_gc) ;  
        tmp = tmp->next;
		
    }
}