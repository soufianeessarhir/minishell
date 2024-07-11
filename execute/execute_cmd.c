/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:34:58 by relamine          #+#    #+#             */
/*   Updated: 2024/07/11 17:12:15 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *get_path(char **argv,t_gc **l_gc)
{
	char *env_path;
	char *path_env_copy;
	char **split_paths;
	char *path_check;

	env_path = getenv("PATH");
    if (env_path == NULL)
        return (NULL);
	path_env_copy = ft_strdup(env_path,l_gc);
    if (path_env_copy == NULL)
        return (NULL);
	split_paths = ft_split(path_env_copy, ':',l_gc);
	if (split_paths == NULL) 
		return (NULL);
	while (*split_paths)
	{
		path_check = ft_strjoin(*split_paths, "/",l_gc);
		if (path_check == NULL)
			return (NULL);
		path_check = ft_strjoin(path_check, argv[0],l_gc);
		if (path_check == NULL)
			return (NULL);
		if (access(path_check, X_OK) == 0)
            return (free(path_env_copy), path_check);
		free(path_check);
		split_paths++;
	}
	return (NULL);
}

int ft_execute(char **argv, char **envp,t_gc **l_gc)
{
	char *path_cmd;
	pid_t childpid;
	
	if (argv[0][0] != '/')
		path_cmd = get_path(argv,l_gc);
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
		{
			perror("execve");
			exit(errno);
		}
    }
    return 0;
}

