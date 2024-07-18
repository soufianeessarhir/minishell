/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:27:31 by relamine          #+#    #+#             */
/*   Updated: 2024/07/14 02:51:19 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	*skip_slash(char *str)
{
	int i;
	char *command;
	int bol;
	char *get_char;

	i = 0;
	command = NULL;
	while (str[i])
	{
		bol = 0;
		get_char = ft_substr(str, i, 1);
		if (get_char == NULL)
			return (NULL);
		command = ft_strjoin(command, get_char);
		if (command == NULL)
			return (NULL);
		while (str[i] == '/')
		{
			bol = 1;
			i++;
		}
		if (!bol)
			i++;
	}
	i = ft_strlen(command) - 1;
	if (i != 0 && command[i - 1] != '.' && command[i] == '/' && command[i + 1] == '\0')
		command[i] = '\0';
	return (command);
}

void cd(char **argv, char ***envp)
{
	int		i;
	int		j;
	char	*path;
	t_env *env_lst;

	i = 1;
	j = 0;
	path = argv[i];
	env_lst = NULL;
	intit_env_list(&env_lst, *envp);
	if (path == NULL || ft_strcmp(path, "~") == 0)
		path = my_getenv("HOME", env_lst);
	else
		path = skip_slash(path);
	// export OLDPWD
	export_oldpwd(envp);
	// change directory
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(": ", 1);
		perror("");
	}
	// export PWD
	export_pwd(envp);
}
