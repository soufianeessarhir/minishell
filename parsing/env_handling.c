/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/09 15:56:14 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int sp_in_it(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return 1;
		i++;
	}
	return 0;
}
int is_all_dollar(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '$' && str[i] != ' ' && str[i] != '\'' && str[i] != '\"')
			return 1;
		i++;
	}
	return 0;
}
char *expand_double_dollar(char *str, t_gc **l_gc)
{
	int i = 0;
	char *result = ft_strdup("", l_gc);
	char *tmp;
	char *tmp2;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			tmp = ft_strdup("pid", l_gc);
			result = ft_strjoin(result, tmp, l_gc);
			i += 2;
		}
		else
		{
			tmp2 = ft_substr(str, i, 1, l_gc);
			result = ft_strjoin(result, tmp2, l_gc);
			i++;
		}
	}
	return result;
}

t_env_vars *new_env_vars(char *value, t_gc **l_gc) 
{
    t_env_vars *new = ft_malloc(sizeof(t_env_vars), l_gc);
    if (!new)
        return NULL;
    new->value = value;
    new->next = NULL;
    return new;
}

void env_lstadd_back(t_env_vars **alst, t_env_vars *new) 
{
    t_env_vars *tmp;
    if (!*alst)
    {
        *alst = new;
        return;
    }
    tmp = *alst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}


int is_dollar(char *str) 
{
    while (*str) 
    {
        if (*str == '$')
            return 1;
        str++;
    }
    return 0;
}

char *clean_str(char *str, t_gc **l_gc) 
{
    int i = 0, j = 0;
    char quote;
    char *tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
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
    tmp[j] = '\0';
    return tmp;
}

char *env_search(char *str, t_env *env_lst, t_gc **l_gc, int numcmd) 
{
    int i = 0, j = 0;
    char *result = NULL;
    
	if (str[0] == '\'')
         return ft_strdup(str, l_gc);
	str = expand_double_dollar(str, l_gc); 
    while (str[i]) 
    {
        if (str[i] == '$' && str[i + 1] != '/')
        {
			if (str[i + 1] == '?' && str[0] != '\'')
            {
				if (numcmd == 0)
                	result = ft_strjoin(result, my_getenv( "exitstatus", env_lst), l_gc);
				else
					result = ft_strjoin(result, "0", l_gc);
                i += 2;
            }
			else
			{
	            j = ++i;
	            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' ) )
	                i++;
	            if (str[j] != '\'' && str[j] != '\"')
	                result = ft_strjoin(result, my_getenv(ft_substr(str, j, i - j, l_gc), env_lst), l_gc);
	            else
	                result = ft_strjoin(result, ft_substr(str, j - 1, i - j + 1, l_gc), l_gc);
			}
        }
        else
        {
            j = i;
			if (str[i] == '$')
			   i++;
            while (str[i] != '$' && str[i])
                i++;
            result = ft_strjoin(result, ft_substr(str, j, i - j, l_gc), l_gc);
        }
    }
    return result;
}


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