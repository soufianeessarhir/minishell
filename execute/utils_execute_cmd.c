/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execute_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 17:50:00 by relamine          #+#    #+#             */
/*   Updated: 2024/08/17 17:55:41 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void handle_relative_path_error(char *path_cmd)
{
	struct stat	statbuf;

	if (!ft_strncmp(path_cmd, "./", 2) || !ft_strncmp(path_cmd, "../", 2) || (ft_strncmp(path_cmd, "/", 1) && ft_strchr(path_cmd, '/')))
	{
		stat(path_cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(path_cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
		perror(path_cmd);
		if (errno == 13)
			exit(126);
		exit(127);
	}
}
static void handle_absolute_path_error(char *path_cmd)
{
	struct stat	statbuf;

	if (!ft_strncmp(path_cmd, "/", 1))
	{
		stat(path_cmd, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			ft_putstr_fd(path_cmd, 2);
			ft_putstr_fd(": is a directory\n", 2);
			exit(126);
		}
		perror(path_cmd);
		if (errno == 13)
			exit(126);
		exit(127);
	}
}
void handle_execve_error(char *path_cmd, t_env *env_lst)
{
	ft_putstr_fd("minishell: ", 2);
	handle_relative_path_error(path_cmd);
	handle_absolute_path_error(path_cmd);
	if (my_getenv("PATH", env_lst) == NULL)
	{
		ft_putstr_fd(path_cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(path_cmd, 2);
		ft_putstr_fd(": command not found\n", 2);		
	}
	exit(127);
}

void   reset_terminal()
{
	char *cmd = "/bin/stty";
    char *argv[] = {"stty", "sane", NULL};
    char *envp[] = {NULL};

	int pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0) 
	{
		if (execve(cmd, argv, envp) == -1)
			perror("execve failed");
	}
	else
		waitpid(pid, NULL, 0);
}