/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:57:12 by relamine          #+#    #+#             */
/*   Updated: 2024/08/19 06:36:04 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_double(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_isonlydigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (ft_isdigit(str[0]))
		return (1);
	while (str[i])
	{
		if (ft_isalpha(str[i]) || str[i] == '_')
			return (0);
		i++;
	}
	return (1);
}

char	*get_key(char *str, t_gc **gc)
{
	int		i;
	char	*key;

	i = 0;
	if (str && str[i] == '=')
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		if (ft_strlen(str) >= 3 && i != 0 && str[i] == '+' && str[i + 1] == '=')
			break ;
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (NULL);
		i++;
	}
	key = ft_substr(str, 0, i, gc);
	return (key);
}

char	*get_value(char *str, t_gc **gc)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
		return (NULL);
	i++;
	value = ft_strdup(str + i, gc);
	if (value == NULL)
		return (NULL);
	return (value);
}
