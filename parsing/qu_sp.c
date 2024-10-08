/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qu_sp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 20:50:02 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 08:52:21 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_exist(char *str, char c, int *i)
{
	while (str[++(*i)] != '\0')
	{
		if (str[*i] == c)
			return (1);
		if (str[*i] == '\\')
			return (0);
	}
	return (0);
}

int	sp_uq_handling(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if ((line[i] == '\'' && !is_exist(line, '\'', &i))
			|| (line[i] == '\"' && !is_exist(line, '\"', &i)))
			return (printf("minishell: input not allowed\n"), 1);
		if (line[i] == '\\' || line[i] == ';')
			return (printf("minishell: input not allowed\n"), 1);
	}
	return (0);
}
