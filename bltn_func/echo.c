/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 08:33:52 by relamine          #+#    #+#             */
/*   Updated: 2024/07/15 01:52:28 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_handling_n(const char *s1)
{
	size_t			i;
	unsigned char	*st1;

	st1 = (unsigned char *)s1;
	if (st1[0] == '-' && st1[1] == 'n')
	{
		i = 2;
		while (st1[i] == 'n')
			i++;
		if (st1[i] == '\0')
			return (0);
	}
	return (1);
}

int echo(int argc, char **argv, char **envp)
{
	int flag_n;
	int index;
	t_env *env_lst;
	
	flag_n = 0;
	index = 1;
	env_lst = NULL;
	intit_env_list(&env_lst, envp);
	while (index < argc && ft_handling_n(argv[index]) == 0)
	{
		flag_n = 1;
		index++;
	}
	while (index < argc)
	{
		if (ft_strcmp(argv[index], "~") == 0)
			argv[index] = my_getenv("HOME", env_lst);
		ft_putstr_fd(argv[index], 1);
		if (index + 1 < argc)
			ft_putstr_fd(" ", 1);
		index++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);

	return (0);
}
