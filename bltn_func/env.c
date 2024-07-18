/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:17:27 by relamine          #+#    #+#             */
/*   Updated: 2024/07/17 05:20:34 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int env(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		if (!ft_strchr(env[i], '=') && get_value(env[i]) == NULL)
		{
			i++;
			continue;
		}
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
