/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/27 09:21:00 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export_arg(t_token *token_lst, char *str)
{
	t_token	*tmp;
	int		i;

	tmp = token_lst;
	i = 0;
	while (str && str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '$')
			return (0);
		i++;
	}
	while (tmp->prev && tmp->prev->type != 3)
		tmp = tmp->prev;
	if (tmp && tmp->value && strcmp(tmp->value, "export") == 0)
		return (1);
	return (0);
}

void	norm_helper(char *tmp_va, t_gc **l_gc, char **value)
{
	tmp_va = trem_doubled_double_qoutes(tmp_va, l_gc);
	if (tmp_va && tmp_va[0] == '\"' && tmp_va[1] != '\"')
		return ;
	ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ",
				tmp_va, l_gc), ": ambiguous redirect\n", l_gc), 2);
	*value = NULL;
}

static void	init(int *i, t_token **tmp, t_token *token_lst)
{
	*i = 0;
	*tmp = token_lst;
}

static void	increment(int *i, int type)
{
	if (type == 3)
		*i = *i + 1;
}

void	env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc)
{
	t_token	*tmp;
	int		numcmd;

	init(&numcmd, &tmp, *token_lst);
	while (tmp)
	{
		tmp->is_env = 0;
		if (tmp->type == 1)
		{
			if (is_dollar(tmp->value) && (!(tmp->prev
						&& ft_strcmp(tmp->prev->value, "<<") == 0)))
				norm_env_zero(&tmp, env_lst, l_gc, &numcmd);
			else
				tmp->value = ft_strdup(clean_str(tmp->value, l_gc), l_gc);
		}
		else
			tmp->value = ft_strdup(clean_str(tmp->value, l_gc), l_gc);
		increment(&numcmd, tmp->type);
		tmp = tmp->next;
	}
}
