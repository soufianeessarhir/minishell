/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:50:33 by relamine          #+#    #+#             */
/*   Updated: 2024/08/08 08:46:42 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char *get_key_unset(char *str, t_gc **gc)
{
	int i;
	char *key;

	i = 0;
	if (str && ft_strchr(str, '=') != NULL)
		return (NULL);
	if (ft_isdigit(str[0]) || str[0] == '\0')
		return (NULL);
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_') || ft_iswhitespace(str[i]))
			return (NULL);
		i++;
	}
	key = ft_substr(str, 0, i, gc);
	return (key);
}

int unset(char **argv, char ***env_lst, t_gc **gc, t_gc **lst)
{
	int i;
	int j;
	int k;
	char *key;
	char **new_env;
	int status;

	i = 1;
	status = 0;
	while (argv[i] != NULL)
	{
		key = get_key_unset(argv[i], gc);
		if (key == NULL)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
			i++;
			continue;
		}
		j = 0;
		k = 0;
		new_env = ft_malloc(sizeof(char *) * (ft_strlen_double(*env_lst) + 1), lst);
		while ((*env_lst)[j] != NULL)
		{
			if (ft_strcmp(get_key((*env_lst)[j], gc), key) != 0)
			{
				new_env[k] = ft_strdup((*env_lst)[j], lst);
				k++;
			}
			j++;
		}
		new_env[k] = NULL;
		*env_lst = new_env;
		i++;
	}
	return (status);
}	
