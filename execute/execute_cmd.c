/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:34:58 by relamine          #+#    #+#             */
/*   Updated: 2024/07/20 13:34:00 by relamine         ###   ########.fr       */
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
            return (path_check);
		split_paths++;
	}
	return (argv[0]);
}

int ft_execute(char **argv, char ***envp, t_gc **l_gc, t_gc **lst)
{
	char *path_cmd;
	pid_t childpid;
	t_env *env_lst;
	char *num_shlvl;
	char **shelvl;

	env_lst = NULL;
	intit_env_list(&env_lst, *envp, l_gc);
	if (strchr(argv[0], '/') == NULL)
		path_cmd = get_path(argv, env_lst, l_gc);
	else
		path_cmd = argv[0];
	childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		return 1;
	}
	if (childpid > 0)
        wait(NULL);
	if (childpid == 0)
    {
		if (ft_strcmp(path_cmd, "./minishell") == 0)
		{
			num_shlvl = my_getenv("SHLVL", env_lst);
			int i = ft_atoi(num_shlvl);
			if (i == 0 || i >= 10240)
				i = 1;
			else if (i < 0)
				i = 0;
			else
				i++;
			num_shlvl = ft_strjoin("SHLVL=", ft_itoa(i, l_gc) ,l_gc);
			shelvl = ft_malloc(sizeof(char *) * 3, l_gc);
			shelvl[0] = ft_strdup("export", l_gc);
			shelvl[1] = num_shlvl;
			shelvl[2] = NULL;
			ft_export(shelvl, envp, l_gc, lst);
		}
		if (execve(path_cmd, argv, *envp) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(errno);
		}
    }
    return 0;
}

