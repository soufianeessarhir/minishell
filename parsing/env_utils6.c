/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:04:47 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/27 09:22:35 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_env_for(char *s, int *i, t_gc **l_gc, t_env_vars **new)
{
	while (s[*i])
	{
		if (s[*i] == '$')
			process_dor(s, i, l_gc, new);
		else if (s[*i] == '\'' || s[*i] == '\"')
			process_quote(s, i, l_gc, new);
		else
			process_reg(s, i, l_gc, new);
	}
}

void	clean_st_heler(char *str, int *i, int *j, char *result)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
	{
		if (str[*i])
		{
			result[*j] = str[*i];
			(*j)++;
		}
		(*i)++;
	}
	if (str[*i] == quote)
		(*i)++;
}

void	norm_env_zero(t_token **tmp, t_env *env_lst, t_gc **l_gc, int *numcmd)
{
	char	*tmp_va;

	tmp_va = (*tmp)->value;
	(*tmp)->value = helper((*tmp)->value, l_gc, env_lst, *numcmd);
	if (((*tmp)->value == NULL || sp_in_it((*tmp)->value))
		&& (*tmp)->prev && (*tmp)->prev->type == 2)
		norm_helper(tmp_va, l_gc, &(*tmp)->value);
	else if (!is_export_arg(*tmp, tmp_va))
		(*tmp)->is_env = 1;
}

char	*deter_spl(char *str, char *ostr, t_gc **l_gc)
{
	char	*res;
	int		i;

	if (ostr[0] == '\'' || ostr[0] == '\"' || !str)
		return (str);
	i = 0;
	res = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			res[i] = '\\';
		else
			res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*undeter_spl(char *str, t_gc **l_gc)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	res = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	while (str[i])
	{
		if (str[i] == '\\')
			res[j] = ' ';
		else
			res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
