/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/22 14:40:47 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export_status (int status, char ***envp, t_gc **l_gc, t_gc **lst)
{
	char *tmp;
	char **exitstatus;

	tmp = ft_strjoin("exitstatus=", ft_itoa(status, l_gc) ,l_gc);
	exitstatus = ft_malloc(sizeof(char *) * 3, l_gc);
	exitstatus[0] = ft_strdup("export", l_gc);
	exitstatus[1] = tmp;
	exitstatus[2] = NULL;
	ft_export(exitstatus, envp, l_gc, lst, 0);
}


void ft_builtin_func(char **argv, char ***envpv, t_gc **gc, t_gc **lst, int *bol)
{
	int i;
	int status;

	//FOR ECHO
	i = 0;
	status = 0;
	if (argv == NULL || argv[i] == NULL)
		return;
	if (ft_strcmp(argv[i], "echo") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		status = echo(i, argv, envpv, lst);
		export_status(status, envpv, gc, lst);
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
		status = pwd();
		export_status(status, envpv, gc, lst);
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
		return;
	}


	//FOR ENV
	i = 0;
	if (ft_strcmp(argv[i], "env") == 0)
	{
		status = env(*envpv, gc, *bol);
		export_status(status, envpv, gc, lst);
		return;
	}

	//FOR CD
	if (ft_strcmp(argv[i], "cd") == 0)
	{
		status = cd(argv, envpv, gc, lst);
		export_status(status, envpv, gc, lst);
		return;
	}

	//FOR EXPORT
	if (ft_strcmp(argv[i], "export") == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		status = ft_export(argv, envpv, gc, lst, bol);
		export_status(status, envpv, gc, lst);
		return;
	}
	
	// FOR UNSET
	i = 0;
	if (ft_strncmp(argv[i], "unset", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		status = unset(argv, envpv, gc, lst);
		export_status(status, envpv, gc, lst);
		return;
	}

	//FOR EXUCUTE COMMAND
	ft_execute(argv, envpv, gc, lst);

}
