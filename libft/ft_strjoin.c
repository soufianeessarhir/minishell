/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:57 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/07 08:42:45 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	newstr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!newstr)
		return (NULL);
	while (*s1)
	{
		newstr[i] = *s1++; 
		i++;
	}
	while (*s2)
	{
		newstr[i] = *s2++;
		i++;
	}
	*(newstr + i) = '\0';
	return (newstr);
}
