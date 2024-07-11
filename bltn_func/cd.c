/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:27:31 by relamine          #+#    #+#             */
/*   Updated: 2024/07/11 17:09:03 by sessarhi         ###   ########.fr       */
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
		if (get_char == NULL)
			return (NULL);
		command = ft_strjoin(command, get_char,l_gc);
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

void cd(char **argv,t_gc **l_gc)
{
	int		i;
	int		j;
	char	*path;

	i = 1;
	j = 0;

	path = argv[i];
	if (path == NULL)
		path = getenv("HOME");
	else
		path = skip_slash(path,l_gc);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(argv[i], 1);
		ft_putstr_fd(": ", 1);
		perror("");
	}; 
}
