/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/08/14 00:26:06 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *str, t_gc **gc)
{
	int		i;
	char	*key;

	i = 0;
	if (str && str[i] == '=')
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		if (ft_strlen(str) >= 3 && i != 0 && str[i] == '+' && str[i + 1] == '=')
			break ;
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (NULL);
		i++;
	}
	key = ft_substr(str, 0, i, gc);
	return (key);
}

char	*get_value(char *str, t_gc **gc)
{
	int		i;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
		return (NULL);
	i++;
	value = ft_strdup(str + i, gc);
	if (value == NULL)
		return (NULL);
	return (value);
}

// Function to combine environment variables and arguments
void	combine_env_and_args(char ***envp, char *argv, t_gc **lst)
{
	size_t	env_count = ft_strlen_double(*envp);
	char	**new_env = ft_malloc(sizeof(char *) * (env_count + 2), lst);
	size_t	i = 0;

	while (i < env_count)
	{
		new_env[i] = ft_strdup((*envp)[i], lst);
		i++;
	}
	new_env[i] = ft_strdup(argv, lst);
	i++;
	new_env[i] = NULL;
	*envp = new_env;
}

char	**sort_env_list(char ***env_lst, t_gc **gc)
{
	char	**tmp;
	char	**tmp2;
	char	*swap;
	int	j;

	size_t	env_count = ft_strlen_double(*env_lst);
	char	**new_env = ft_malloc(sizeof(char *) * (env_count + 1), gc);
	size_t	i = 0;

	while (i < env_count)
	{
		new_env[i] = ft_strdup((*env_lst)[i], gc);
		i++;
	}
	new_env[i] = NULL;	
	tmp = new_env;
	i = 0;
	j = 0;
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

// Function to print exported environment variables
void	print_exported_variables(char **envp, t_gc **gc, int bol)
{
	int	i = 0;
	char	**env;

	env = sort_env_list(&envp, gc);
	while (env[i])
	{
		if (ft_strcmp(get_key(env[i], gc), "PATH") == 0 && bol == 1)
		{
			i++;
			continue ;
		}
		if (!ft_strcmp(get_key(env[i], gc), "exitstatus") || !ft_strncmp(env[i], "@path_of_program", 16) || !ft_strcmp(get_key(env[i], gc), "_"))
		{
			i++;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		if (strchr(env[i], '=') == NULL)
			printf("%s\n", env[i]);
		else if (get_value(env[i], gc) == NULL && strchr(env[i], '=') != NULL)
			printf("%s\"\"\n", env[i]);
		else
			printf("%s=\"%s\"\n", get_key(env[i], gc), get_value(env[i], gc));
		i++;
	}
	
}

int	ft_export(char **argv, char ***envp, t_gc **gc, t_gc **lst, int *boll)
{
	int		g;
	int		i;
	int		j;
	int		bol;
	char	*tmp;
	int		status;

	status = 0;
	g = ft_strlen_double(argv);
	if (g == 1)
		return (print_exported_variables(*envp, gc, *boll), 0);
	i = 1;
	if (ft_strcmp(get_key(argv[i], gc), "PATH") == 0 && boll != 0)
		*boll = 0;
	while (argv[i])
	{
		if (get_key(argv[i], gc) == NULL || ft_isonlydigit(get_key(argv[i], gc)))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
		{
			bol = 0;
			j = 0;
			while ((*envp)[j] != NULL)
			{
				if (ft_strcmp(get_key((*envp)[j], gc), get_key(argv[i], gc)) == 0)
				{
					bol = 1;
					if (ft_strchr(argv[i], '=') == NULL)
						break ;
					if (ft_strchr(argv[i], '+') != NULL)
					{
						tmp = get_value(argv[i], gc);
						(*envp)[j] = ft_strjoin((*envp)[j], tmp, lst);
					}
					else
						(*envp)[j] = ft_strdup(argv[i], lst);
					break ;
				}
				j++;
			}
			if (bol == 0)
			{
				if (ft_strchr(argv[i], '+') != NULL)
				{
					tmp = get_value(argv[i], gc);
					argv[i] = ft_strjoin(get_key(argv[i], gc), "=", gc);
					argv[i] = ft_strjoin(argv[i], tmp, lst);
					combine_env_and_args(envp, argv[i], lst);
				}
				else
					combine_env_and_args(envp, argv[i], lst);
			}
		}
		i++;
	}
	return (status);
}
