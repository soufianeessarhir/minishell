/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 05:12:18 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/11 07:36:14 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// void process_dolar(char *s, int *i, t_gc **l_gc, t_env_vars **new)
// {
// 	int j;
// 	char *substr;
// 	t_env_vars *tmp;

// 	tmp = NULL;
// 	substr = NULL;
// 	j = *i;
// 	(*i)++;
// 	while (s[*i] && s[*i] == '$')
// 		(*i)++;
// 	while (s[*i] && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
// 		(*i)++;
// 	substr = ft_substr(s, j, *i - j, l_gc);
// 	if (substr && *substr)
// 	{
// 		new_env_vars(substr, l_gc);
// 		env_lstadd_back(new, tmp);
// 	}	
// }

// void process_regular(char *s, int *i, t_gc **l_gc, t_env_vars **new)
// {
// 	int j;
// 	char *substr;
// 	t_env_vars *tmp;
	
// 	j = *i;
// 	substr = NULL;
// 	tmp = NULL;
// 	while (s[*i] && s[*i] != '\'' && s[*i] != '\"' && s[*i] != '$')
// 		(*i)++;
// 	substr = ft_substr(s, j, *i - j, l_gc);
// 	if (substr && *substr)
// 	{
// 		new_env_vars(substr, l_gc);
// 		env_lstadd_back(new, tmp);
// 	}
// }
// void  process_quote(char *s, int *i, t_gc **l_gc, t_env_vars **new)
// {
//     int j;
//     t_env_vars *tmp;
//     char *substr;
//     char quote ;

//     substr = NULL;
//     tmp = NULL;
//     j = *i;
//     quote = s[*i];
// 	(*i)++;
//     while (s[*i] && s[*i] != quote) 
//         (*i)++;
//     substr = ft_substr(s, j, *i - j + 1, l_gc);
//     if (substr && *substr)
//     {
//         new_env_vars(substr, l_gc);
//         env_lstadd_back(new, tmp);
//     } 
// 	if (s[*i] == quote)
// 		(*i)++;
// }
// char *new_value(t_env_vars *new,t_gc **l_gc)
// {
// 	t_env_vars *tmp;
// 	char *new_value;
	
// 	tmp = new;
// 	new_value = NULL;
// 	while (tmp)
// 	{
// 		new_value = ft_strjoin(new_value, tmp->value, l_gc);
// 		tmp = tmp->next;
// 	}
// 	return new_value;
// }
// char *helper(char *s, t_gc **l_gc, t_env *env_lst, int numcmd)
// {
//     t_env_vars *new;
// 	t_env_vars *tmp;
//     int i;

// 	new = NULL;
// 	i = 0;
//     while (s[i])
//     {
//         if (s[i] == '$')
// 			process_dolar(s, &i, l_gc,&new);
//         else if (s[i] != '\'' && s[i] != '\"')
//            process_regular(s, &i, l_gc, &new);
//         else if (s[i] == '\'' || s[i] == '\"')
// 			process_quote(s, &i, l_gc, &new);
// 		else
// 			i++;
//     }
//     tmp = new;
//     while (tmp)
//     {
// 		if (!is_all_dollar(tmp->value) && !tmp->next)
// 		     tmp->value = expand_double_dollar(tmp->value, l_gc);
//         else if (is_dollar(tmp->value))
//             tmp->value = env_search(tmp->value, env_lst, l_gc, numcmd);
//         tmp = tmp->next;
//     }
// 	return (new_value(new, l_gc));
// }