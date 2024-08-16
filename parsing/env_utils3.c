/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 02:59:18 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/15 11:41:03 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_h_init(t_env_h *env_h, t_gc **l_gc, t_env *env_lst, char *str)
{
	env_h->i = 0;
	env_h->result = NULL;
	env_h->tmp = NULL;
	env_h->env_lst = env_lst;
	env_h->l_gc = l_gc;
	env_h->str = str;
}

void	env_pro_max(t_env_h *tmp, int numcmd)
{
	if (tmp->str[tmp->i] && tmp->str[tmp->i + 1] == '?')
	{
		tmp->result = handle_exit_status(tmp->result,
				tmp->env_lst, tmp->l_gc, numcmd);
		tmp->i += 2;
	}
	else if (tmp->str[tmp->i] == '$'
		&& !ft_strcmp(&tmp->str[tmp->i + 1], "_"))
	{
		if (numcmd == 0)
			tmp->result = handle_env_variable(tmp->str, &tmp->i,
					tmp->result, tmp);
		else
		{
			tmp->result = ft_strjoin(tmp->result, "", tmp->l_gc);
			tmp->i += 2;
		}
	}
	else
		tmp->result = handle_env_variable(tmp->str, &tmp->i,
				tmp->result, tmp);
}

char	*env_search(char *str, t_env *env_lst, t_gc **l_gc, int numcmd)
{
	t_env_h	tmp;

	env_h_init(&tmp, l_gc, env_lst, str);
	if (str[0] == '\'' && numcmd != -1)
		return (ft_strdup(str, l_gc));
	str = expand_double_dollar(str, l_gc);
	while (str[tmp.i])
	{
		if (str[tmp.i] == '$' && !str[tmp.i + 1])
			tmp.i++;
		if (str[tmp.i] == '$' && str[tmp.i + 1] != '/')
			env_pro_max(&tmp, numcmd);
		else if (str[tmp.i])
			tmp.result = handle_non_variable(str, &tmp.i, tmp.result, l_gc);
	}
	return (tmp.result);
}
