/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 09:44:02 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 06:29:22 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len, t_gc **gc)

{
	char			*str;
	size_t			i;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0 || start > s_len)
		return (ft_strdup("", gc));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_malloc(len + 1, gc);
	if (!str)
		return (NULL);
	ft_memset(str, 0, len + 1);
	i = 0;
	while (i < len)
	{
		str[i] = *(s + i + start);
		i++;
	}
	str[i] = '\0';
	return (str);
}
