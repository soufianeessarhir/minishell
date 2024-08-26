/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:13:53 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/26 12:32:32 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trem_doubled_double_qoutes(char *str, t_gc **l_gc)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_malloc(ft_strlen(str) + 1, l_gc);
	while (str[i])
	{
		if (str[i +1] && str[i] == '\"' && str[i + 1] == '\"')
			i += 2;
		else
		{
			result[j] = str[i];
			i++;
			j++;
		}
	}
	result[j] = '\0';
	return (result);
}
