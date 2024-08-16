/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 23:37:11 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 17:09:20 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str, t_gc **gc)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = ft_malloc(sizeof(char ) * (ft_strlen(str) + 1), gc);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
