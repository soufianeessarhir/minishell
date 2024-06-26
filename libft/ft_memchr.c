/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:02:51 by sessarhi          #+#    #+#             */
/*   Updated: 2023/11/12 01:23:46 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	unsigned char		b;

	i = 0;
	str = s;
	b = c;
	while (i < n)
	{
		if (str[i] == b)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
