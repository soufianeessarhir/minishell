/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:38:11 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 11:28:50 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	len;

	len = 0;
	if (!*s)
		return (1);
	while (*s != '\0')
	{
		if (*s != c && *s)
		{
			len++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (len);
}


static int	ft_countchars(char const *s, char c, int i)
{
	int	j;

	j = 0;
	while (s[i] != c && s[i])
	{
		j++;
		i++;
	}
	return (j);
}

static char	**ft_strfill(const char *s, char c, int size, t_gc **gc)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = ft_malloc(sizeof(char *) * (size + 1), gc);
	if (!ptr)
		return (NULL);
	while (j < size)
	{
		while (s[i] == c)
			i++;
		ptr[j] = ft_substr(s, i, ft_countchars(s, c, i), gc);
		if (ptr[j] == NULL)
			return (NULL);
		i = i + ft_countchars(s, c, i);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c, t_gc **gc)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_strfill(s, c, ft_countwords(s, c), gc);
	return (str);
}
