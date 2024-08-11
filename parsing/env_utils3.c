/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 02:59:18 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/11 06:39:04 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *clean_str(char *str, t_gc **l_gc) 
{
    int i;
	int j;
    char quote;
    char *tmp;
	
	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	i = 0;
	j = 0;
    if (!tmp)
        return NULL;
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
    return (tmp[j] = '\0',tmp);
}

static char *handle_exit_status(char *result, t_env *env_lst, t_gc **l_gc, int numcmd)
{
    if (numcmd == 0)
        return ft_strjoin(result, my_getenv("exitstatus", env_lst), l_gc);
    else
        return ft_strjoin(result, "0", l_gc);
}

static char *handle_env_variable(char *str, int *i, char *result, t_env *env_lst, t_gc **l_gc)
{
    int j = ++(*i);
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    if (str[j] != '\'' && str[j] != '\"')
        return ft_strjoin(result, my_getenv(ft_substr(str, j, *i - j, l_gc), env_lst), l_gc);
    else
        return ft_strjoin(result, ft_substr(str, j - 1, *i - j + 1, l_gc), l_gc);
}

static char *handle_non_variable(char *str, int *i, char *result, t_gc **l_gc)
{
    int j = *i;
    if (str[*i] == '$')
        (*i)++;
    while (str[*i] != '$' && str[*i])
        (*i)++;
    return ft_strjoin(result, ft_substr(str, j, *i - j, l_gc), l_gc);
}

char *env_search(char *str, t_env *env_lst, t_gc **l_gc, int numcmd) 
{
    int i;
    char *result;

	i = 0;
	result = NULL;
    if (str[0] == '\'')
        return ft_strdup(str, l_gc);
    str = expand_double_dollar(str, l_gc); 
    while (str[i]) 
    {
        if (str[i] == '$' && str[i + 1] != '/')
        {
            if (str[i + 1] == '?')
            {
                result = handle_exit_status(result, env_lst, l_gc, numcmd);
                i += 2;
            }
            else if (str[i] == '$' && !ft_strcmp(&str[i + 1], "_"))
			{
				if (numcmd == 0)
					result = handle_env_variable(str, &i, result, env_lst, l_gc);
				else
				{
					result = ft_strjoin(result, "", l_gc);
					i += 2;
				}
			}
			else
                result = handle_env_variable(str, &i, result, env_lst, l_gc);
        }
        else
            result = handle_non_variable(str, &i, result, l_gc);
    }
    return result;
}
