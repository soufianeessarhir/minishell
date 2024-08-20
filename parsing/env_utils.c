/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:17:21 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/20 14:29:39 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*new_env(char *key, char *value, t_gc **lst)
{
	t_env	*new;

	new = ft_malloc(sizeof(t_env), lst);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	env_add_back(t_env **env_lst, t_env *new)
{
	t_env	*tmp;

	if (!*env_lst)
		*env_lst = new;
	else
	{
		tmp = *env_lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	intit_env_list(t_env **env_lst, char **env, t_gc **lst)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i] && env[i][j] != '\0' && env[i][j] != '=' )
			j++;
		key = ft_substr(env[i], 0, j, lst);
		value = ft_substr(env[i], j + 1, ft_strlen(env[i]) - j - 1, lst);
		if (!*env_lst)
			*env_lst = new_env(key, value, lst);
		else
			env_add_back(env_lst, new_env(key, value, lst));
		i++;
	}
}

char	*my_getenv(char *key, t_env *env_lst)
{
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

int	sp_in_it(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	j = ft_strlen(str) - 1;
	while (i <= j && (str[i] == ' ' || str[i] == '\\'))
		i++;
	if (i > j)
		return (1);
	while (j >= i && (str[j] == ' ' || str[j] == '\\'))
		j--;
	while (str[i] && i <= j)
	{
		if (str[i] == ' ' || str[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}
