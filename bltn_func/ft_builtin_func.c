/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/19 22:26:46 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void ft_builtin_func(char **argv, char **envp, t_gc **l_gc)
{
	int i;


	//FOR ECHO
	i = 0;
	if (ft_strcmp(argv[i], "echo") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		echo(i, argv);
		return;
	}

	//FOR PWD
	i = 0;
	if (ft_strcmp(argv[i], "pwd") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		pwd();
		return;
	}

	//FOR EXIT
	i = 0;
	if(ft_strcmp(argv[i], "exit") == 0)
	{
		int j;
		int k;
		long checker;
		int argc;

		i++;
		j = 0;
		argc = ft_strlen_double(argv + 1);
		if (argv[i] != NULL && ft_strnstr(argv[i], "|", argc) == NULL)
		{
			k = 0;
			checker = ft_atoi_checker(argv[i]);
			if (argc >= 2 && checker != -1 && checker != -2)
			{
				ft_putstr_fd("exit\n", 1);
				ft_putstr_fd("minishell: exit: too many arguments\n", 1);
				return;
			}
			else if (checker == -1 || checker == -2)
			{
				ft_putstr_fd("exit\n", 1);
				ft_putstr_fd("minishell: exit: ", 1);
				ft_putstr_fd(argv[i], 1);
				ft_putstr_fd(": numeric argument required\n", 1);
				exit_0(255);
			}
			else
			{
				ft_putstr_fd("exit\n", 1);
				exit_0(checker);
			}
			i++;
		}
		ft_putstr_fd("exit\n", 1);
		exit_0(0);
		return;
	}


	//FOR ENV
	i = 0;
	if (ft_strcmp(argv[i], "env") == 0)
	{
		env(envp);
		return;
	}

	if (ft_strcmp(argv[i], "cd") == 0)
	{
		cd(argv, l_gc);
		return;
	}

	//FOR EXPORT
	if (ft_strcmp(argv[i], "export") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		// export(argv, envp);
	}

	//FOR EXUCUTE COMMAND
	ft_execute(argv, envp, l_gc);

	//FOR UNSET
	// i = 0;
	// if (ft_strncmp(argv[i], "unset", ft_strlen(argv[i])) == 0)
	// {
	// 	i++;
	// 	while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
	// 		i++;
	// 	unset(argv[1], envp);
	// }
	
}
