/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:21:12 by relamine          #+#    #+#             */
/*   Updated: 2024/08/05 18:55:43 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exit_0(int i, int argc, char **argv)
{
	int j;
	long checker;
	int error_msg;

	j = 0;
	ft_putstr_fd("exit\n", 1);
	if (argv[i] != NULL)
	{
		error_msg = 0;
		checker = ft_atoi_checker(argv[i], &error_msg);
		if (argc >= 2 && error_msg != -1 && error_msg != -2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			if (argc > 2)
				return ;
			exit(1);
		}
		else if ((error_msg == -1 || error_msg == -2))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		else
			exit(checker);
	}
	exit(0);
}
