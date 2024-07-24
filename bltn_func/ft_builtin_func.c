/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/24 16:24:22 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_builtin_func(char **argv, char ***envpv, t_gc **gc, t_gc **lst, int *bol)
{
	int i;
	int status;

	i = 0;
	status = 0;
	if (argv == NULL || argv[i] == NULL)
		return (-9999);

	if (!ft_strcmp(argv[i], "echo"))
		return (echo(ft_strlen_double(argv),argv, envpv, lst));
	else if (!ft_strcmp(argv[i], "pwd"))
		return (pwd());
	else if (!ft_strcmp(argv[i], "env"))
		return (env(*envpv, gc, *bol));
	else if (!ft_strcmp(argv[i], "cd"))
		return (cd(argv, envpv, gc, lst));
	else if (!ft_strcmp(argv[i], "export"))
		return (ft_export(argv, envpv, gc, lst, bol));
	else if (!ft_strncmp(argv[i], "unset", ft_strlen(argv[i])))
		return (unset(argv, envpv, gc, lst));
	else if(!ft_strcmp(argv[i], "exit"))
	{
		int j;
		int k;
		long checker;
		int argc;

		i++;
		j = 0;
	
		ft_putstr_fd("exit\n", 1);
		argc = ft_strlen_double(argv + 1);
		if (argv[i] != NULL && ft_strnstr(argv[i], "|", argc) == NULL)
		{
			k = 0;
			checker = ft_atoi_checker(argv[i]);
			if (argc >= 2 && checker != -1 && checker != -2)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				exit_0(1);
			}
			else if (checker == -1 || checker == -2)
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(argv[i], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				exit_0(255);
			}
			else
				exit_0(checker);
		}
		exit_0(0);
	}
	//FOR EXUCUTE COMMAND
	return (ft_execute(argv, envpv, gc, lst));
}
