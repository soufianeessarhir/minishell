/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:34:58 by relamine          #+#    #+#             */
/*   Updated: 2024/07/26 19:36:45 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_path(char **argv,  t_env *env_lst, t_gc **l_gc)
{
	char *env_path;
	char *path_env_copy;
	char **split_paths;
	char *path_check;

	env_path = my_getenv("PATH", env_lst);
    if (env_path == NULL)
        return (argv[0]);
	path_env_copy = ft_strdup(env_path,l_gc);
	split_paths = ft_split(path_env_copy, ':',l_gc);
	while (*split_paths)
	{
		path_check = ft_strjoin(*split_paths, "/",l_gc);
		path_check = ft_strjoin(path_check, argv[0],l_gc);
		if (access(path_check, X_OK) == 0)
            return (path_check);
		split_paths++;
	}
	return (argv[0]);
}

int ft_execute(t_cmd *cmd, char ***envp, t_gc **l_gc, t_gc **lst)
{
	char **argv;
	char *path_cmd;
	pid_t childpid;
	t_env *env_lst;
	int status;
	struct stat statbuf;

	env_lst = NULL;
	status = 0;
	argv = cmd->args;
	intit_env_list(&env_lst, *envp, l_gc);
	if (strchr(argv[0], '/') == NULL)
		path_cmd = get_path(argv, env_lst, l_gc);
	else
		path_cmd = argv[0];
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (childpid > 0)
	{
		if (*cmd->flag_pipe != 1)
			ft_export_anything(ft_strjoin("_=", path_cmd, l_gc), l_gc, lst, envp);
		g_a.stpsignal_inparent = 1;
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			status = 128 + WTERMSIG(status);
		if (status == 130)
			printf("\n");
		if (status == 131)
			printf("Quit: 3\n");
		g_a.stpsignal_inparent = 0;
		g_a.exitstatus_singnal = 0;
	}
	if (childpid == 0)
    {
		if (ft_strcmp(path_cmd, "./minishell") == 0)
		{
			export_shelvl(envp, l_gc, lst, env_lst);
			if (ft_strcmp(getcwd(NULL, 0), "/Users/relamine/Desktop/minishell"))
				path_cmd = ft_strjoin("/Users/relamine/Desktop/minishell/", path_cmd, l_gc);
		}
		if (execve(path_cmd, argv, *envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			stat(path_cmd, &statbuf);
			if (S_ISDIR(statbuf.st_mode))
			{
				ft_putstr_fd(argv[0], 2);
				ft_putstr_fd(": is a directory\n", 2);
			}
			else if (strchr(argv[0], '/'))
				perror(argv[0]);
			else
			{
				ft_putstr_fd(argv[0], 2);
				ft_putstr_fd(": command not found\n", 2);
			}
			exit(127);
		}
    }
	return (status);
}

