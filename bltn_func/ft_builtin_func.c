/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/07/06 14:22:36 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		pwd(NULL);
	}

}

