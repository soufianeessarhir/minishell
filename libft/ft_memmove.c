/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:34:17 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 06:16:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)(dst);
	s = (const unsigned char *)(src);
	if (d < s)
		ft_memcpy(d, s, len);
	else if (d > s)
	{
		while (len --)
			d[len] = s[len];
	}
	return (dst);
}
