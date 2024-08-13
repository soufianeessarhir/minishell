/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:44:50 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/13 02:54:26 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_str(char *str, t_gc **l_gc)
{
	int		i;
	int		j;
	char	quote;
	char	*tmp;

	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	i = 0;
	j = 0;
	if (!tmp || !str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				tmp[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			tmp[j++] = str[i++];
	}
	return (tmp[j] = '\0', tmp);
}

char	*handle_exit_status(char *result, t_env *env_lst,
	t_gc **l_gc, int numcmd)
{
	if (numcmd == 0)
		return (ft_strjoin(result, my_getenv("exitstatus", env_lst), l_gc));
	else
		return (ft_strjoin(result, "0", l_gc));
}

char	*handle_env_variable(char *str, int *i, char *result, t_env_h *tmp)
{
	int	j;

	j = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	if (str[j] != '\'' && str[j] != '\"')
		return (ft_strjoin(result, my_getenv(ft_substr(str, j, *i - j,
						tmp->l_gc), tmp->env_lst), tmp->l_gc));
	else
		return (ft_strjoin(result,
				ft_substr(str, j - 1, *i - j + 1, tmp->l_gc), tmp->l_gc));
}

char	*handle_non_variable(char *str, int *i, char *result, t_gc **l_gc)
{
	int	j;

	j = *i;
	if (str[*i] == '$')
		(*i)++;
	while (str[*i] != '$' && str[*i])
		(*i)++;
	return (ft_strjoin(result, ft_substr(str, j, *i - j, l_gc), l_gc));
}
