/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/08 18:22:25 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_builtin_func(char **argv, char **envp)
{
	int i;

	//FOR ECHO
	i = 0;
	if (ft_strncmp(argv[i], "echo", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		echo(i, argv);
	}

	//FOR PWD
	i = 0;
	if (ft_strncmp(argv[i], "pwd", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		pwd();
	}

	//FOR EXIT
	i = 0;
	if(ft_strncmp(argv[i], "exit", ft_strlen(argv[i])) == 0)
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
	}


	//FOR ENV
	i = 0;
	if (ft_strncmp(argv[i], "env", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		env(envp);
	}

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
