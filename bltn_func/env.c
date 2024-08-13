/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:17:27 by relamine          #+#    #+#             */
/*   Updated: 2024/08/13 07:12:52 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **env, t_gc **lst, int bol)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp(get_key(env[i], lst), "PATH") == 0 && bol == 1)
		{
			i++;
			continue ;
		}
		if (ft_strcmp(get_key(env[i], lst), "exitstatus") == 0 || ft_strncmp(env[i], "@path_of_program", 16) == 0)
		{
			i++;
			continue ;
		}
		if ((!ft_strchr(env[i], '=') && get_value(env[i], lst) == NULL))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
