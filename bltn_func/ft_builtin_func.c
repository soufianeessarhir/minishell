/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/18 04:30:34 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_builtin_func(char **argv, char ***envpv, t_gc **gc, t_gc **lst)
{
	int i;

	//FOR ECHO
	i = 0;
	if (ft_strcmp(argv[i], "echo") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		echo(i, argv, *envpv, lst);
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
		env(*envpv, gc);
		return;
	}

	//FOR CD
	if (ft_strcmp(argv[i], "cd") == 0)
	{
		cd(argv, envpv, gc, lst);
		return;
	}

	//FOR EXPORT
	if (ft_strcmp(argv[i], "export") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		ft_export(argv, envpv, gc, lst);
		return;
	}
	
	//FOR EXUCUTE COMMAND
	ft_execute(argv, envpv, gc, lst);

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
