/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:34:58 by relamine          #+#    #+#             */
/*   Updated: 2024/07/09 08:36:33 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_path(char **argv)
{
	char *env_path;
	char *path_env_copy;
	char **split_paths;
	char *path_check;

	env_path = getenv("PATH");
    if (env_path == NULL)
        return (NULL);
	path_env_copy = ft_strdup(env_path);
    if (path_env_copy == NULL)
        return (NULL);
	split_paths = ft_split(path_env_copy, ':');
	if (split_paths == NULL) 
		return (NULL);
	while (*split_paths)
	{
		path_check = ft_strjoin(*split_paths, "/");
		if (path_check == NULL)
			return (NULL);
		path_check = ft_strjoin(path_check, argv[0]);
		if (path_check == NULL)
			return (NULL);
		if (access(path_check, X_OK) == 0)
            return (free(path_env_copy), path_check);
		free(path_check);
		split_paths++;
	}
	return (NULL);
}

int ft_execute(char **argv, char **envp)
{
	char *path_cmd;
	pid_t childpid;
	
	if (argv[0][0] != '/')
		path_cmd = get_path(argv);
	else
		path_cmd = argv[0];
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		return 1;
	}
	if (childpid > 0)
    {
        wait(NULL);
    }
	if (childpid == 0)
    {
		if (execve(path_cmd, argv, envp) == -1)
			return (perror("execve"), 1);

    }
    return 0;
}

