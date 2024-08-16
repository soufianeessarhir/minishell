/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 17:16:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_export_arg(t_token *token_lst)
{
	t_token	*tmp;

	tmp = token_lst;
	while (tmp->prev && tmp->prev->type != 3)
		tmp = tmp->prev;
	if (tmp && tmp->value && strcmp(tmp->value, "export") == 0)
		return (1);
	return (0);
}

void	norm_helper(char *tmp_va, t_gc **l_gc, char **value)
{
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
	char	*tmp_va;
	int		numcmd;

	init(&numcmd, &tmp, *token_lst);
	while (tmp)
	{
		tmp->is_env = 0;
		if (tmp->type == 1)
		{
			if (is_dollar(tmp->value) && (!(tmp->prev
					&& ft_strcmp(tmp->prev->value, "<<") == 0)))
			{
				tmp_va = tmp->value;
				tmp->value = helper(tmp->value, l_gc, env_lst, numcmd);
				if ((tmp->value == NULL || sp_in_it(tmp->value))
					&& tmp->prev && tmp->prev->type == 2)
					norm_helper(tmp_va, l_gc, &tmp->value);
				else if (!is_export_arg(tmp))
					tmp->is_env = 1;
			}
			else 
				tmp->value = ft_strdup(clean_str(tmp->value, l_gc), l_gc);
		}
		else 
			tmp->value = ft_strdup(clean_str(tmp->value, l_gc), l_gc);
		increment(&numcmd, tmp->type);
		tmp = tmp->next;
	}
}
