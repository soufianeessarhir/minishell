/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/07 18:35:59 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_builtin_func(char **argv)
{
	int i;

	i = 0;
	if (ft_strncmp(argv[i], "echo", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		echo(i, argv);
	}

	i = 0;
	if (ft_strncmp(argv[i], "pwd", ft_strlen(argv[i])) == 0)
	{
		i++;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
			i++;
		pwd();
	}
	if(ft_strncmp(argv[i], "exit", ft_strlen(argv[i])) == 0)
	{
		int j;
		int k;
		int bol;

		i++;
		j = 0;
		while (argv[i] != NULL && ft_strnstr(argv[i], "|", ft_strlen(argv[i])) == NULL)
		{
			k = 0;
			bol = 0;
			if (!ft_atoi(argv[i]) && i == 1)
			{
				ft_putstr_fd("exit\n", 1);
				ft_putstr_fd("minishell: exit: ", 1);
				ft_putstr_fd(argv[i], 1);
				ft_putstr_fd(": numeric argument required\n", 1);
				exit_0(255);
			}
			
			i++;
		}
		exit_0(j);
	}

}

			// ft_putstr_fd("exit\n", 1);
			// 	ft_putstr_fd("minishell: exit: ", 1);
			// 	ft_putstr_fd(argv[i], 1);
			// 	ft_putstr_fd(": numeric argument required\n", 1);
			// 	exit(255);