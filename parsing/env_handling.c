/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/11 16:52:38 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *clear_close_quotes(char *str,t_gc **l_gc)
{
	int i;
	int j;
	char quote;
	char *tmp;

	i = 0;
	j = 0;
	tmp = ft_malloc(sizeof(char) * (ft_strlen(str) + 1), l_gc);
	ft_memset(tmp, 0, ft_strlen(str) + 1);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			if (str[i + 1] == quote)
				i+= 2;
			else
			{
				tmp[j++] = str[i++];
				while (str[i] && str[i] != quote)
					tmp[j++] = str[i++];
				tmp[j++] = str[i++];  
			}
		}
		else
			tmp[j++] = str[i++];
	}
	return tmp;

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

char *cleand_str(char *str) 
{
	int i;
	int j;
	char quote;
	
	i = 0;
	j = 0;
	
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				str[j++] = str[i++];
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return str;
}	
int is_expandabe(char *str,int start,int end,t_gc **l_gc) 
{	
	(void)end;
	start++;
	if(check_ex(ft_substr(str, 0, start ,l_gc),start))
		return 0;

	return 1;
}

char *env_search(char *str,t_env *env_lst, t_gc **l_gc) 
{
	t_env_vars *tmp;
	

	tmp = ft_malloc(sizeof(t_env_vars), l_gc);
	tmp->i = 0;
	tmp->j = 0;
	tmp->result = NULL;
	str = clear_close_quotes(str,l_gc);
	while (str[tmp->i]) 
	{
		if (str[tmp->i] == '$')
		{
			if (str[tmp->i + 1] == '?')
			{
				tmp->result = ft_strjoin(tmp->result, ft_itoa(errno,l_gc), l_gc);
				tmp->i += 2;
				continue;
			}
			tmp->j = tmp->i;
			tmp->i++;
			while ((ft_isalnum(str[tmp->i]) || str[tmp->i] == '_' ) && str[tmp->i])
				tmp->i++;
			if (is_expandabe(str,tmp->j - 1,tmp->i,l_gc))
				tmp->result = ft_strjoin(tmp->result,my_getenv(ft_substr(str, tmp->j + 1, tmp->i - tmp->j - 1,l_gc), env_lst), l_gc);
			else
				tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j,l_gc), l_gc);
			tmp->j = tmp->i;
		}
		else
		{
			tmp->j = tmp->i;
			while (str[tmp->i] != '$' && str[tmp->i])
				tmp->i++;
			tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j,l_gc), l_gc);
		}
		
	}
	return (cleand_str(tmp->result));  
}

void env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc) 
{
	t_token *tmp;
	char *new_value;
	tmp = *token_lst;
	new_value = NULL;
	while (tmp) 
	{
		if (tmp->type == 1 )
		{
			if (is_dollar(tmp->value))
			{
				new_value = env_search(tmp->value, env_lst, l_gc);
				free(tmp->value);
				tmp->value = new_value;
			}
			else
				tmp->value = cleand_str(tmp->value);
		}
		tmp = tmp->next;
	}
}