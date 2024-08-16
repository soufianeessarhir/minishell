/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:50:33 by relamine          #+#    #+#             */
/*   Updated: 2024/08/16 01:10:25 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_unset_error(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
int	ft_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*get_key_unset(char *str, t_gc **gc)
{
	int		i;
	char	*key;

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

char **create_new_env(char **env, char *key, t_gc **gc, t_gc **lst)
{
	int j;
	int k;
	char **new_env;
	t_env	*env_lst;

	env_lst = NULL;
	intit_env_list(&env_lst, env, gc);
    if (!my_getenv(key, env_lst))
		return (env);
	j = 0;
	k = 0;
	new_env = ft_malloc(sizeof(char *) * (ft_strlen_double(env)), lst);
	while (env[j] != NULL)
	{
		if (ft_strcmp(get_key(env[j], gc), key) != 0)
			new_env[k++] = ft_strdup(env[j], lst);
		j++;
	}
	new_env[k] = NULL;
	return (new_env);
}

int	unset(char **argv, char ***env_lst, t_gc **gc, t_gc **lst)
{
	int		i;
	char	*key;
	int		status;

	i = 1;
	status = 0;
	while (argv[i] != NULL)
	{
		key = get_key_unset(argv[i], gc);
		if (key == NULL)
		{
			print_unset_error(argv[i++]);
			status = 1;
			continue ;
		}
		*env_lst = create_new_env(*env_lst, key, gc, lst);
		i++;
	}
	return (status);
}	
