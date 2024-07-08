/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:57:12 by relamine          #+#    #+#             */
/*   Updated: 2024/07/08 00:46:32 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


long ft_atoi_checker(char *str)
{
	int		signe;
	long	res;

	signe = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
		if (*str == '\0')
			return(-1);
	}
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			signe = -1;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		if (res > 922337203685477580 || (res == 922337203685477580 && *str > '7' && signe == 1) ||
			(res == 922337203685477580 && *str > '8' && signe == -1))
			return (-2);
		res = res * 10 + (*(str++) - '0');
	}
	return (res * signe);
}


int ft_strlen_double(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}
