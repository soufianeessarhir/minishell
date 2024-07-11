/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 22:38:11 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/11 17:13:13 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countwords(char const *s, char c)
{
    int	len;
    char   quote;

    len = 0;
    while (*s != '\0')
    {
        if (*s == '\'' || *s == '\"')
        {
            quote = *s;
            s++;
            while (*s != quote && *s)
                s++;		
        }
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
    char quote;

    j = 0;
    while (s[i] != c && s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            quote = s[i];
            i++;
            j++;
            while (s[i] != quote && s[i])
            {
                j++;
                i++;
            }
            j++;
            i++;
        }
        else
        {
            j++;
            i++;
        }
    }
    return (j);
}

static char	**ft_strfill(const char *s, char c, int size, t_gc **gc)
{
    int		i;
    int		j;
    char	**ptr;

    i = -1;
    j = -1;
    ptr = ft_malloc(sizeof(char *) * (size + 1), gc);
    if (!ptr)
        return (NULL);
    while (++j < ft_countwords(s, c))
    {
        while (s[++i] == c)
            ;
        ptr[j] = ft_substr(s, i, ft_countchars(s, c, i), gc);
        if (ptr[j] == NULL)
            return (my_free(ptr),NULL);
        i = i + ft_countchars(s, c, i);
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