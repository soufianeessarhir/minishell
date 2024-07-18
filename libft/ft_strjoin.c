/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 11:48:57 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/14 17:07:30 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, t_gc **gc)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, gc));
	if (!s2)
		return (ft_strdup(s1, gc));
	newstr = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), gc);
	if (!newstr)
		return (NULL);
	ft_memset(newstr, 0, ft_strlen(s1) + ft_strlen(s2) + 1);
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
