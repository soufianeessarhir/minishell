/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/07/09 08:24:59 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_key(char *str)
{
	int i;
	char *key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (key == NULL)
		return (NULL);
	return (key);
}

char *get_value(char *str)
{
	int i;
	char *value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	value = ft_substr(str, i, ft_strlen(str) - i);
	if (value == NULL)
		return (NULL);
	return (value);
}

// void export(char **argv, char ***envp)
// {
// 	int i

// 	i = 0;
// 	while ()
// 	{
		
// 	}
	
// }
