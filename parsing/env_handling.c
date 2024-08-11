/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/11 07:36:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char *helper(char *s, t_gc **l_gc, t_env *env_lst, int numcmd)
{
    t_env_vars *new = NULL, *tmp = NULL;
    char *new_value = NULL;
    int i = 0, j;
    char *substr;

    while (s[i])
    {
        if (s[i] == '$')
        {
            j = i;
			i++;
            while (s[i] && s[i] == '$')
                i++;
            while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
                i++;
            substr = ft_substr(s, j, i - j, l_gc);
            if (substr && *substr)
            {
                tmp = new_env_vars(substr, l_gc);
                env_lstadd_back(&new, tmp);
            }
        }
        else if (s[i] != '\'' && s[i] != '\"')
        {
            j = i;
            while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != '$')
                i++;
            substr = ft_substr(s, j, i - j, l_gc);
            if (substr && *substr)
            {
                tmp = new_env_vars(substr, l_gc);
                env_lstadd_back(&new, tmp);
            }
        }
        else if (s[i] == '\'' || s[i] == '\"')
        {
            char quote = s[i++];
            j = i - 1;
            while (s[i] && s[i] != quote)
                i++;
            substr = ft_substr(s, j, i - j + 1, l_gc);
            if (substr && *substr)
            {
                tmp = new_env_vars(substr, l_gc);
                env_lstadd_back(&new, tmp);
            }
            if (s[i] == quote)
                i++;
        }
    }

    tmp = new;
    while (tmp)
    {
		if (!is_all_dollar(tmp->value) && !tmp->next)
		     tmp->value = expand_double_dollar(tmp->value, l_gc);
        else if (is_dollar(tmp->value))
            tmp->value = env_search(tmp->value, env_lst, l_gc, numcmd);
        tmp = tmp->next;
    }

    tmp = new;
    while (tmp)
    {
        new_value = ft_strjoin(new_value, tmp->value, l_gc);
        tmp = tmp->next;
    }
    return new_value;
}

int env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc) 
{
    t_token *tmp = *token_lst;
	char *tmp_va;
	int numcmd = 0;
    while (tmp) 
    {
        if (tmp->type == 1)
        {
            if (is_dollar(tmp->value) && (!tmp->prev || ft_strcmp(tmp->prev->value, "<<") != 0))
			{
				tmp_va = tmp->value;
                tmp->value = helper(tmp->value, l_gc, env_lst, numcmd);
				if ((tmp->value == NULL || sp_in_it(tmp->value)) && tmp->prev && tmp->prev->type == 2)
				{
					ft_putstr_fd(ft_strjoin(ft_strjoin("minishell: ", tmp_va, l_gc), ": ambiguous redirect\n", l_gc),2);
					tmp->value = NULL;
					tmp->is_env = 0;
				}
				else
					tmp->is_env = 1;
			}
            else
				tmp->is_env = 0;
        }
		if (ft_strcmp(tmp->value, "|") == 0)
			numcmd++;
        tmp = tmp->next;
    }
	return 0;
}
