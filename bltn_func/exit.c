/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 09:21:12 by relamine          #+#    #+#             */
/*   Updated: 2024/07/26 14:19:05 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exit_0(int i, int argc, char **argv)
{
	int j;
	long checker;

	j = 0;
	ft_putstr_fd("exit\n", 1);
	if (argv[i] != NULL && ft_strnstr(argv[i], "|", argc) == NULL)
	{
		checker = ft_atoi_checker(argv[i]);
		if (argc >= 2 && checker != -1 && checker != -2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(1);
		}
		else if (checker == -1 || checker == -2)
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
