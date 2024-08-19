/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_display_exported_var.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:41:11 by relamine          #+#    #+#             */
/*   Updated: 2024/08/19 06:52:31 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**copy_env_list(char ***env_lst, t_gc **gc)
{
	size_t	env_count;
	char	**new_env;
	size_t	i;

	i = 0;
	env_count = ft_strlen_double(*env_lst);
	new_env = ft_malloc(sizeof(char *) * (env_count + 1), gc);
	while (i < env_count)
	{
		new_env[i] = ft_strdup((*env_lst)[i], gc);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static char	**sort_env_list(char ***env_lst, t_gc **gc)
{
	char	**tmp;
	char	**tmp2;
	char	*swap;
	int		j;
	int		i;

	i = 0;
	tmp = copy_env_list(env_lst, gc);
	while (tmp[i])
	{
		tmp2 = &tmp[i + 1];
		j = 0;
		while (tmp2 && tmp2[j])
		{
			if (ft_strcmp(tmp[i], tmp2[j]) > 0)
			{
				swap = tmp2[j];
				tmp2[j] = ft_strdup(tmp[i], gc);
				tmp[i] = ft_strdup(swap, gc);
			}
			j++;
		}
		i++;
	}
	return (tmp);
}

static void	print_export_(char *env, t_gc **gc)
{
	ft_putstr_fd("declare -x ", 1);
	if (strchr(env, '=') == NULL)
		printf("%s\n", env);
	else if (get_value(env, gc) == NULL && strchr(env, '=') != NULL)
		printf("%s\"\"\n", env);
	else
		printf("%s=\"%s\"\n", get_key(env, gc), get_value(env, gc));
}

void	print_exported_variables(char **envp, t_gc **gc, int bol)
{
	int		i;
	char	**env;

	env = sort_env_list(&envp, gc);
	i = 0;
	while (env[i])
	{
		if (ft_strcmp(get_key(env[i], gc), "PATH") == 0 && bol == 1)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(env[i], "@exitstatus", 11)
			|| !ft_strncmp(env[i], "@path_of_program", 16)
			|| !ft_strcmp(get_key(env[i], gc), "_")
			|| !ft_strncmp(env[i], "@hidden_PATH", 12))
		{
			i++;
			continue ;
		}
		print_export_(env[i], gc);
		i++;
	}
}
