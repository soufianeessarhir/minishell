/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 02:49:30 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/12 07:04:59 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_all_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_double_dollar(char *str, t_gc **l_gc)
{
	int		i;
	char	*result;
	char	*tmp;
	char	*tmp2;

	i = 0;
	result = ft_strdup("", l_gc);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			tmp = ft_strdup("pid", l_gc);
			result = ft_strjoin(result, tmp, l_gc);
			i += 2;
		}
		else
		{
			tmp2 = ft_substr(str, i, 1, l_gc);
			result = ft_strjoin(result, tmp2, l_gc);
			i++;
		}
	}
	return (result);
}

t_env_vars	*new_env_vars(char *value, t_gc **l_gc)
{
	t_env_vars	*new;

	new = ft_malloc(sizeof(t_env_vars), l_gc);
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_lstadd_back(t_env_vars **alst, t_env_vars *new)
{
	t_env_vars	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	is_dollar(char *str)
{
	while (*str)
	{
		if (*str == '$')
			return (1);
		str++;
	}
	return (0);
}
