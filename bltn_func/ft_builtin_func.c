/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/24 09:08:39 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_builtin_func(char **argv, char ***envpv, t_gc **gc, t_gc **lst, int *bol)
{
	int i;
	int status;

	//FOR ECHO
	i = 0;
	status = 0;
	if (argv == NULL || argv[i] == NULL)
		return (-9999);
	if (ft_strcmp(argv[i], "echo") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		return (echo(i, argv, envpv, lst));
	}

	//FOR PWD
	i = 0;
	if (ft_strcmp(argv[i], "pwd") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		pwd();
		return (pwd());
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
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				exit_0(1);
			}
			else if (checker == -1 || checker == -2)
			{
				ft_putstr_fd("exit\n", 2);
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
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
	if (ft_strcmp(argv[i], "env") == 0)
	{
		return (env(*envpv, gc, *bol));
	}

	//FOR CD
	if (ft_strcmp(argv[i], "cd") == 0)
	{
		return (cd(argv, envpv, gc, lst));
	}

	//FOR EXPORT
	if (ft_strcmp(argv[i], "export") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		return (ft_export(argv, envpv, gc, lst, bol));
	}
	
	// FOR UNSET
	i = 0;
	if (ft_strncmp(argv[i], "unset", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		return (unset(argv, envpv, gc, lst));
	}

	//FOR EXUCUTE COMMAND
	return (ft_execute(argv, envpv, gc, lst));

	// int j = ft_strlen_double(argv);
	// char **tmp;
	// tmp = ft_malloc(sizeof(char *) * 3, lst);
	// tmp[0] = ft_strdup("export", gc);
	// tmp[1] = ft_strjoin("_=", ft_strdup(argv[j], gc), gc);
	// tmp[2] = NULL;
	// ft_export(tmp, envpv, gc, lst, 0);
}
