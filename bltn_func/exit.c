/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:21:12 by relamine          #+#    #+#             */
/*   Updated: 2024/08/16 00:31:11 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int print_exit_error(int argc, int error_msg, int checker, char *arg)
{
	if (argc >= 2 && error_msg != -1 && error_msg != -2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		if (argc > 2)
			return (1);
		exit(1);
	}
	else if ((error_msg == -1 || error_msg == -2))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else
		exit(checker);
}

int	exit_0(int i, int argc, char **argv, int *flag_pipe)
{
	int		j;
	long	checker;
	int		error_msg;

	j = 0;
	if (*flag_pipe != 1)
		ft_putstr_fd("exit\n", 1);
	if (argv[i] != NULL)
	{
		error_msg = 0;
		checker = ft_atoi_checker(argv[i], &error_msg);
		if (print_exit_error(argc, error_msg, checker, argv[i]))
			return (1);
	}
	exit(0);
}
