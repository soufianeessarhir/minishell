/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 01:34:58 by relamine          #+#    #+#             */
/*   Updated: 2024/08/30 03:43:20 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path(char	**argv, t_env *env_lst, t_gc **l_gc)
{
	char	*env_path;
	char	*path_env_copy;
	char	**split_paths;
	char	*path_check;

	env_path = my_getenv("PATH", env_lst);
	if (env_path == NULL)
		return (argv[0]);
	path_env_copy = ft_strdup(env_path, l_gc);
	split_paths = ft_split(path_env_copy, ':', l_gc);
	while (*split_paths)
	{
		path_check = ft_strjoin(*split_paths, "/", l_gc);
		path_check = ft_strjoin(path_check, argv[0], l_gc);
		if (access(path_check, F_OK) == 0)
			return (path_check);
		split_paths++;
	}
	return (argv[0]);
}

static char	*get_command_path(t_cmd *cmd, t_env *env_lst, t_gc **l_gc)
{
	if (ft_strchr(cmd->args[0], '/') == NULL && ft_strlen(cmd->args[0]) != 0)
		return (get_path(cmd->args, env_lst, l_gc));
	else
		return (cmd->args[0]);
}

static int	handle_parent_process(void)
{
	int	status;

	g_a.stpsignal_inparent = 1;
	wait(&status);
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else
		status = WEXITSTATUS(status);
	g_a.stpsignal_inparent = 0;
	if (status == 130)
		printf("\n");
	if (status == 131)
	{
		printf("Quit: 3\n");
		reset_terminal();
	}
	return (status);
}

static pid_t	fork_process(int *flag_pipe, t_norm lst_n)
{
	pid_t	childpid;

	childpid = 0;
	if (!*flag_pipe)
		childpid = fork();
	if (childpid == -1)
	{
		perror("fork");
		return (ft_free(lst_n.l_gc), ft_free(lst_n.lst), exit(1), 1);
	}
	return (childpid);
}

int	ft_execute(t_cmd *cmd, char ***envp, t_norm lst_n)
{
	char		**argv;
	char		*path_cmd;
	pid_t		childpid;
	t_env		*env_lst;

	env_lst = NULL;
	argv = cmd->args;
	intit_env_list(&env_lst, *envp, lst_n.l_gc);
	path_cmd = get_command_path(cmd, env_lst, lst_n.l_gc);
	childpid = fork_process(cmd->flag_pipe, lst_n);
	if (childpid == 0)
	{
		if (ft_strcmp(path_cmd, "minishell") == 0)
			path_cmd = cmd->path_of_program;
		handling_fd_minishell(cmd, path_cmd);
		if (execve(path_cmd, argv, *envp) == -1)
			handle_execve_error(path_cmd, argv[0], env_lst, lst_n);
	}
	return (handle_parent_process());
}
