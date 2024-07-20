/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:50:33 by relamine          #+#    #+#             */
/*   Updated: 2024/07/20 11:55:00 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_key_unset(char *str, t_gc **gc)
{
	int i;
	char *key;

	i = 0;
	if (str[i] && ft_strchr(str, '=') != NULL)
		return (NULL);
	while (str[i])
	{
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (NULL);
		i++;
	}
	key = ft_substr(str, 0, i, gc);
	return (key);
}

void unset(char **argv, char ***env_lst, t_gc **gc, t_gc **lst)
{
	int i;
	int j;
	int k;
	char *key;
	char **new_env;

	i = 1;
	while (argv[i] != NULL)
	{
		key = get_key_unset(argv[i], gc);
		if (key == NULL)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
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
}	