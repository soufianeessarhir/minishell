/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 05:09:21 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/20 14:31:31 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <errno.h>

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		if (errno == ENOENT)
			return (0);
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}

int	handle_red_in(t_cmd *tmp, t_gc **l_gc, t_redir *rd)
{
	if (rd->next && !rd->next->redio)
		return (1);
	if (rd->next && is_directory(rd->next->redio))
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						rd->next->redio, l_gc),
					": Is a directory\n", l_gc), 2), 1);
	if (rd->next && access(rd->next->redio, F_OK) == -1)
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						rd->next->redio, l_gc),
					": No such file or directory\n", l_gc), 2), 1);
	if (tmp->red_in_fd != 0)
		close(tmp->red_in_fd);
	tmp->red_in_fd = open(rd->next->redio, O_RDONLY);
	if (rd && ft_strcmp(rd->redio, "<<") == 0)
		unlink(rd->next->redio);
	if (tmp->red_in_fd == -1)
		return (1);
	return (0);
}

int	handle_append_redirection(t_cmd *tmp, char *redout, t_gc **l_gc)
{
	if (!redout)
		return (1);
	if (redout && is_directory(redout))
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": Is a directory\n", l_gc), 2), 1);
	if ((redout && access(redout, F_OK) == -1
			&& !is_directory(trim_dir(redout, l_gc)) && is_path(redout))
		|| ft_strcmp (redout, "") == 0)
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": No such file or directory\n",
					l_gc), 2), 1);
	if (redout && access(redout, F_OK) == 0 && access(redout, W_OK) == -1)
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": Permission denied\n", l_gc), 2), 1);
	if (tmp->red_out_fd != 1)
		close(tmp->red_out_fd);
	tmp->red_out_fd = open(redout, O_APPEND | O_CREAT | O_RDWR, 0644);
	if (tmp->red_out_fd == -1)
		return (1);
	return (0);
}

int	handle_overwrite_redirection(t_cmd *tmp, char *redout, t_gc **l_gc)
{
	if (!redout)
		return (1);
	if (redout && is_directory(redout))
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": Is a directory\n", l_gc), 2), 1);
	if ((redout && access(redout, F_OK) == -1
			&& !is_directory(trim_dir(redout, l_gc)) && is_path(redout))
		|| ft_strcmp (redout, "") == 0)
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": No such file or directory\n",
					l_gc), 2), 1);
	if (redout && access(redout, F_OK) == 0 && access(redout, W_OK) == -1)
		return (ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
						redout, l_gc), ": Permission denied\n", l_gc), 2), 1);
	if (tmp->red_out_fd != 1)
		close(tmp->red_out_fd);
	tmp->red_out_fd = open(redout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (tmp->red_out_fd == -1)
		return (1);
	return (0);
}

int	handle_red_out(t_cmd *tmp, t_gc **l_gc, t_redir *rd)
{
	if (rd->redio && ft_strcmp(rd->redio, ">") == 0)
	{
		if (rd->next && handle_overwrite_redirection(tmp,
				rd->next->redio, l_gc))
			return (1);
	}
	else if (rd->redio && ft_strcmp(rd->redio, ">>") == 0)
	{
		if (rd->next && handle_append_redirection(tmp, rd->next->redio, l_gc))
			return (1);
	}
	return (0);
}
