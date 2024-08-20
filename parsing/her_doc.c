/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:58:51 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/20 18:38:08 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	rnd(int nd, char *str, t_gc **l_gc)
{
	static int	herdoc;

	herdoc += nd;
	if (nd != 0)
	{
		while (access(ft_strjoin(ft_strjoin("/tmp/heredoc", ft_itoa(herdoc,
							l_gc), l_gc), str, l_gc), F_OK) == 0)
			herdoc += 1;
	}
	return (herdoc);
}

int	hrdc_q_ckeck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}

int	ft_split_here_doc(t_heredoc herdoc, t_gc **l_gc, t_env *env_lst)
{
	if (ft_strcmp (herdoc.line, clean_str(herdoc.delimiter, l_gc)) == 0)
		return (1);
	if (is_dollar(herdoc.line) && !hrdc_q_ckeck(herdoc.delimiter))
		herdoc.line = helper(herdoc.line, l_gc, env_lst, -1);
	write(herdoc.fd, herdoc.line, ft_strlen(herdoc.line));
	write(herdoc.fd, "\n", 1);
	return (0);
}

void	herdoc_h(t_heredoc heredoc, t_token **tmp, t_gc **l_gc, t_env *env_lst)
{
	heredoc.line = readline(">");
	while (isatty(0))
	{
		heredoc.delimiter = (*tmp)->next->value;
		if (!heredoc.line || ft_split_here_doc(heredoc, l_gc, env_lst))
			break ;
		free(heredoc.line);
		heredoc.line = NULL;
		heredoc.line = readline(">");
	}
	if (heredoc.line)
		free(heredoc.line);
	(*tmp)->next->value = ft_strjoin(ft_strjoin("/tmp/heredoc", ft_itoa(rnd(0,
						(*tmp)->next->value, l_gc), l_gc), l_gc),
			(*tmp)->next->value, l_gc);
	close(heredoc.fd);
}

void	her_doc_handling(t_token **token_lst, t_gc **l_gc, t_env *env_lst)
{
	t_token		*tmp;
	t_heredoc	heredoc;

	if (!token_lst || !*token_lst)
		return ;
	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == 2 && strcmp(tmp->value, "<<") == 0)
		{
			if (!tmp->next || (tmp->next->type != 1))
				break ;
			heredoc.fd = open(ft_strjoin(ft_strjoin("/tmp/heredoc", ft_itoa(rnd(
									1, clean_str(tmp->next->value, l_gc), l_gc),
								l_gc), l_gc), clean_str(tmp->next->value, l_gc),
						l_gc), O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (heredoc.fd == -1)
				return ;
			if (isatty(0))
				g_a.stphedorc_insgin = 1;
			herdoc_h(heredoc, &tmp, l_gc, env_lst);
		}
		if (tmp)
			tmp = tmp->next;
	}
}
