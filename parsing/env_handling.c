/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/17 05:44:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int all_dolar(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '$')
			return (0);
		i++;
	}
	return (1);
}
int chaech_quted_dolar(char *str)
{
	int flag = 0;
	int i = 0;
	int flag2 = 0;
	if ((str[0] == '\"' || str[0] == '\'') && (str[ft_strlen(str) - 1] == '\"' || str[ft_strlen(str) - 1] == '\''))
		flag = 1;
    while (str[i])
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			flag2 = 1;
		i++;
	}
	if (flag == 1 && !(flag2 == 1))
		return (1);
	return (0);
}

// Function to create a new environment variable node
t_env_vars *new_env_vars(char *value, t_gc **l_gc) 
{
    t_env_vars *new = ft_malloc(sizeof(t_env_vars), l_gc);
    new->value = value;
    new->next = NULL;
    return new;
}

// Function to add a new environment variable node to the end of the list
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

// Function to remove quotes from a string
char *clear_close_quotes(char *str, t_gc **l_gc)
{
    int i = 0, j = 0;
    char quote;
    char *tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);

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

// Function to check if a string contains a dollar sign
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

// Function to clean a string by removing quotes
char *cleand_str(char *str, t_gc **l_gc) 
{
    int i = 0, j = 0;
    char quote;
    char *tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);

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

// Function to check if a substring is expandable
int is_expandabe(char *str, int start, int end, t_gc **l_gc) 
{
    char *substr = ft_substr(str, 0, start, l_gc);
    int result = check_ex(substr, start);
	(void)end;
    return result == 0;
}

// Function to search for environment variables and replace them in a string
char *env_search(char *str, t_env *env_lst, t_gc **l_gc) 
{
    int i = 0, j = 0;
    t_env_vars *tmp = ft_malloc(sizeof(t_env_vars), l_gc);
    tmp->result = ft_strdup("", l_gc);
    while (str[i]) 
    {
        if (str[i] == '$')
        {
            if (str[i + 1] == '?')
            {
                tmp->result = ft_strjoin(tmp->result, ft_itoa(errno, l_gc), l_gc);
                i += 2;
                continue;
            }
            j = ++i;
            while (ft_isalnum(str[i]) || str[i] == '_')
                i++;
            if (is_expandabe(str, j - 1, i, l_gc))
                tmp->result = ft_strjoin(tmp->result, my_getenv(ft_substr(str, j, i - j, l_gc), env_lst), l_gc);
            else
                tmp->result = ft_strjoin(tmp->result, ft_substr(str, j - 1, i - j + 1, l_gc), l_gc);
        }
        else
        {
            j = i;
            while (str[i] != '$' && str[i])
                i++;
            tmp->result = ft_strjoin(tmp->result, ft_substr(str, j, i - j, l_gc), l_gc);
        }
    }
    return tmp->result;
}
char *remove_dolars(char *str, t_gc **l_gc,int flag)
{
	int i = 0;
	int j = 0;
	char *tmp = ft_strdup("", l_gc);
	while (str[i] == '\"' || str[i] == '\'')
		i++;
	tmp = ft_strjoin(tmp, ft_substr(str, j, i, l_gc), l_gc);
	j = i;
	if (flag == 1)
		tmp = ft_strjoin(tmp, "$", l_gc);
	while (str[i]== '$')
		i++;
	j = i;
	while (str[i])
		i++;
	tmp = ft_strjoin(tmp, ft_substr(str, j, i - j, l_gc), l_gc);
	return tmp;
}
// Helper function to process strings with quotes and environment variables
char *helper(char *s, t_gc **l_gc, t_env *env_lst)
{
   t_env_vars *new = NULL, *tmp = NULL;
    char *new_value = ft_strdup("", l_gc);
    int i = 0, j;
    char *substr;
    
    while (s[i])
    {
        if (s[i] == '$')
        {
            j = i;
            while (s[i] && s[i] == '$')
                i++;
            while (s[i] && s[i] != '\'' && s[i] != '\"'  && s[i] != '$')
                i++;
            substr = ft_substr(s, j, i - j, l_gc);
            if (substr && *substr) 
            {
                tmp = new_env_vars(substr, l_gc);
                env_lstadd_back(&new, tmp);
            }
        }
        if (s[i] != '\'' && s[i] != '\"')
        {
            j = i;
            while (s[i] && s[i] != '\'' && s[i] != '\"')
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
        if (is_dollar(tmp->value) && !chaech_quted_dolar(tmp->value) && !(all_dolar(tmp->value) && !tmp->next))
            tmp->value = env_search(tmp->value, env_lst, l_gc);
		else if (is_dollar(tmp->value) && !chaech_quted_dolar(tmp->value) && all_dolar(tmp->value) && !tmp->next && ft_strlen(tmp->value) % 2 == 1)
			tmp->value = ft_strdup("$", l_gc);
		else if (is_dollar(tmp->value) && !chaech_quted_dolar(tmp->value) && all_dolar(tmp->value) && !tmp->next && ft_strlen(tmp->value) % 2 == 0)
			tmp->value = ft_strdup("", l_gc);
		else if (is_dollar(tmp->value) && chaech_quted_dolar(tmp->value) && ft_strlen(tmp->value) % 2 == 0 && tmp->value[0] == '\"')
			tmp->value = remove_dolars(tmp->value, l_gc,0);
		else if (is_dollar(tmp->value) && chaech_quted_dolar(tmp->value) && ft_strlen(tmp->value) % 2 == 1 && tmp->value[0] == '\"')
			tmp->value = remove_dolars(tmp->value, l_gc,1);
        tmp = tmp->next;
    }

    tmp = new;
    while (tmp)
    {
        new_value = ft_strjoin(new_value, tmp->value, l_gc);
        tmp = tmp->next;
    }
    return cleand_str(new_value, l_gc);
}

// Function to handle environment variables in token list
void env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc) 
{
    t_token *tmp = *token_lst;

    while (tmp) 
    {
        if (tmp->type == 1)
        {
            if (is_dollar(tmp->value))
                tmp->value = helper(tmp->value, l_gc, env_lst);
            else
                tmp->value = cleand_str(tmp->value, l_gc);
        }
        tmp = tmp->next;
    }
}
