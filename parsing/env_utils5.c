/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 07:44:50 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/18 16:52:49 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_qu_exist(char *str, int i)
{
	int		j;
	char	quote;

	j = i;
	quote = str[j++];
	while (str[j] && str[j] != quote)
		j++;
	if (str[j] == quote)
		return (1);
	return (0);
}

char	*clean_str(char *str, t_gc **l_gc)
{
	int		i;
	int		j;
	char	*tmp;

	if (!str)
		return (NULL);
	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"' || str[i] == '\\')
			&& is_qu_exist(str, i))
			clean_st_heler(str, &i, &j, tmp);
		else
			tmp[j++] = str[i++];
	}
	tmp[j] = '\0';
	return (tmp);
}

char	*handle_exit_status(char *result, t_env *env_lst,
	t_gc **l_gc, int numcmd)
{
	if (numcmd == 0)
		return (ft_strjoin(result, my_getenv("@exitstatus", env_lst), l_gc));
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
		return (ft_strjoin(result, expand_sl(my_getenv(ft_substr(str, j, *i - j,
							tmp->l_gc), tmp->env_lst), tmp->l_gc), tmp->l_gc));
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
