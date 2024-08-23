/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 20:57:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/23 16:39:54 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nr_rl_vars(t_cmd **cmd, t_env **env_lst, t_gc **l_gc, char **line)
{
	ft_free(l_gc);
	free(*line);
	*line = NULL;
	*cmd = NULL;
	*env_lst = NULL;
}

void	init_rn_rll(t_norm_rll *help_rll)
{
	help_rll->env_lst = NULL;
	help_rll->l_gc = NULL;
	help_rll->cmd = NULL;
	help_rll->tmp_env = NULL;
}

void	rll_helper1(int *a, int *b)
{
	*a = 1;
	*b = 0;
}

void	rll_helper2(void)
{
	dup2(2, 0);
	dup2(2, 1);
}

void	rll_nr_helpr_f(t_norm_rll *helper)
{
	helper->help.line = *(helper->line);
	helper->help.env = &helper->env;
	helper->help.lst = helper->lst;
}
