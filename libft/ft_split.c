/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:38:11 by sessarhi          #+#    #+#             */
/*   Updated: 2023/11/15 17:25:49 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	len;

	len = 0;
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

static void	my_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
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

static char	**ft_strfill(const char *s, char c, int size)
{
	int		i;
	int		j;
	char	**ptr;

	i = 0;
	j = 0;
	ptr = malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	while (j < ft_countwords(s, c))
	{
		while (s[i] == c)
			i++;
		ptr[j] = ft_substr(s, i, ft_countchars(s, c, i));
		if (ptr[j] == NULL)
		{
			my_free(ptr);
			return (NULL);
		}
		i = i + ft_countchars(s, c, i);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
		return (NULL);
	str = ft_strfill(s, c, ft_countwords(s, c));
	return (str);
}
