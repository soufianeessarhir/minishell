/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:28:19 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/11 17:14:18 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set,t_gc **gc)
{
	size_t	front;
	size_t	end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	if ((*set == '\0' && *s1 == '\0'))
		return (ft_strdup("", gc));
	front = 0;
	end = ft_strlen(s1);
	while (s1[front] && ft_strchr(set, s1[front]))
		front++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end - 1 > front)
		end--;
	str = ft_substr(s1, front, end - front, gc);
	return (str);
}
