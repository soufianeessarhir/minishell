/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:00 by relamine          #+#    #+#             */
/*   Updated: 2024/08/22 15:56:18 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	handle_relative_path_error(char *path_cmd, t_norm lst_n)
{
	struct stat	statbuf;

	if (!ft_strncmp(path_cmd, "./", 2) || !ft_strncmp(path_cmd, "../", 3)
		|| (ft_strncmp(path_cmd, "/", 1) && ft_strchr(path_cmd, '/')))
	{
		stat(path_cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(path_cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(126));
		}
		perror(path_cmd);
		if (errno == 13)
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(126));
		return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(127));
	}
}

static void	handle_absolute_path_error(char *path_cmd, t_norm lst_n)
{
	struct stat	statbuf;

	if (!ft_strncmp(path_cmd, "/", 1))
	{
		stat(path_cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(path_cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(126));
		}
		perror(path_cmd);
		if (errno == 13)
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(126));
		return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(127));
	}
}

void	handle_execve_error(char *path_cmd, char *argv,
	t_env *env_lst, t_norm lst_n)
{
	ft_putstr_fd("minishell: ", 2);
	if (!ft_strcmp(argv, "..") || !ft_strcmp(argv, "."))
		path_cmd = argv;
	handle_relative_path_error(path_cmd, lst_n);
	handle_absolute_path_error(path_cmd, lst_n);
	if (my_getenv("PATH", env_lst) == NULL)
	{
		ft_putstr_fd(path_cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		if (!ft_strcmp(argv, "..") || !ft_strcmp(argv, "."))
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(126));
	}
	else
	{
		ft_putstr_fd(path_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(127));
}

void	reset_terminal(void)
{
	char	*cmd;
	char	*argv[3];
	int		pid;

	cmd = "/bin/stty";
	argv[0] = "stty";
	argv[1] = "sane";
	argv[2] = NULL;
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (execve(cmd, argv, NULL) == -1)
			perror("execve failed");
	}
	else
		waitpid(pid, NULL, 0);
}

void	handling_fd_minishell(t_cmd *cmd, char *path_cmd, t_norm lst_n)
{
	char		*is_minishell;

	is_minishell = ft_strnstr(path_cmd, "./minishell", ft_strlen(path_cmd));
	if (*cmd->flag_pipe && is_minishell && cmd->num_cmd > 0)
		close(1);
	if (cmd->num_cmd == 0 && is_minishell)
	{
		if (dup2(2, 1) == -1)
		{
			perror("dup2");
			return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(1));
		}
	}
}
