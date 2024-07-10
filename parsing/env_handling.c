/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:16:32 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/09 11:35:20 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *clear_close_quotes(char *str)
{
	int i;
	int j;
	char quote;
	char *tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(str) + 1));
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
int is_expandabe(char *str,int start,int end) 
{	
	(void)end;
	start++;
	if(check_ex(ft_substr(str, 0, start ),start))
		return 0;

	return 1;
}

char *env_search(char *str,char **env) 
{
	t_env_vars *tmp;
	t_env *env_lst;

	env_lst = NULL;
	intit_env_list(&env_lst, env);
	tmp = malloc(sizeof(t_env_vars));
	tmp->i = 0;
	tmp->j = 0;
	tmp->result = NULL;
	str = clear_close_quotes(str);
	while (str[tmp->i]) 
	{
		if (str[tmp->i] == '$')
		{
			if (str[tmp->i + 1] == '?')
			{
				tmp->result = ft_strjoin(tmp->result, ft_itoa(errno));
				tmp->i += 2;
				continue;
			}
			tmp->j = tmp->i;
			tmp->i++;
			while ((ft_isalnum(str[tmp->i]) || str[tmp->i] == '_' ) && str[tmp->i])
				tmp->i++;
			if (is_expandabe(str,tmp->j - 1,tmp->i))
				tmp->result = ft_strjoin(tmp->result,my_getenv(ft_substr(str, tmp->j + 1, tmp->i - tmp->j - 1), env_lst));
			else
				tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j));
			tmp->j = tmp->i;
		}
		else
		{
			tmp->j = tmp->i;
			while (str[tmp->i] != '$' && str[tmp->i])
				tmp->i++;
			tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j));
		}
		
	}
	return (cleand_str(tmp->result));  
}

void env_handling(t_token **token_lst, char **env) 
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
				new_value = env_search(tmp->value, env);
				free(tmp->value);
				tmp->value = new_value;
			}
			else
				tmp->value = cleand_str(tmp->value);
		}
		tmp = tmp->next;
	}
}