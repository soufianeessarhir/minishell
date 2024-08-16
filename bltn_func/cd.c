/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:27:31 by relamine          #+#    #+#             */
/*   Updated: 2024/08/16 00:35:54 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*skip_slash(char *str, t_gc **l_gc)
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
		get_char = ft_substr(str, i, 1,l_gc);
		command = ft_strjoin(command, get_char,l_gc);
		while (str[i] == '/')
		{
			bol = 1;
			i++;
		}
		if (!bol)
			i++;
	}
	i = ft_strlen(command) - 1;
	if (i > 0 && command[i - 1] != '.' && command[i] == '/' && command[i + 1] == '\0')
		command[i] = '\0';
	return (command);
}

int cd(char **argv, char ***envp, t_gc **l_gc, t_gc **lst)
{
	int		i;
	int		j;
	char	*path;
	t_env *env_lst;

	i = 1;
	j = 0;
	path = argv[i];
	env_lst = NULL;
	intit_env_list(&env_lst, *envp, l_gc);
	if (path == NULL)
		path = my_getenv("HOME", env_lst);
	else
		path = skip_slash(path, l_gc);
	export_oldpwd(envp, l_gc, lst);
	if (path && chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(": ", 1);
		perror("");
		return (1);
	}
	export_pwd(envp, l_gc, lst);
	return (0);
}
