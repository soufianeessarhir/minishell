/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/07/24 15:34:41 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_key(char *str, t_gc **gc)
{
	int i;
	char *key;

	i = 0;
	if (str[i] && str[i] == '=')
		return (NULL);
	while (str[i] && str[i] != '=')
	{
		if (ft_strlen(str) >= 3 && i != 0 && str[i] == '+' && str[i + 1] == '=')
			break;
		if ((!ft_isalnum(str[i]) && str[i] != '_'))
			return (NULL);
		i++;
	}
	key = ft_substr(str, 0, i, gc);
	return (key);
}
char *get_value(char *str, t_gc **gc)
{
	int i;
	char *value;

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
void combine_env_and_args(char ***envp, char *argv, t_gc **lst)
{
    size_t env_count = ft_strlen_double(*envp);
    char **new_env = ft_malloc(sizeof(char *) * (env_count + 2), lst);
    // Copy existing environment variables
	size_t i = 0;

	while (i < env_count)
	{
		new_env[i] = ft_strdup((*envp)[i], lst);
		i++;
	}
    
  	new_env[i] = ft_strdup(argv, lst);
	i++;

	new_env[i] = NULL;
    *envp = new_env;
	i=0;
}

// Function to print exported environment variables
void print_exported_variables(char **envp, t_gc **gc, int bol)
{
    int i = 0;
    while (envp[i] != NULL)
	{
		if (ft_strcmp(get_key(envp[i], gc), "PATH") == 0 && bol == 1)
		{
			i++;
			continue;
		}
		if (ft_strcmp(get_key(envp[i], gc), "exitstatus") == 0)
		{
			i++;
			continue;
		}
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(envp[i], 1);
		if (get_value(envp[i], gc) == NULL && strchr(envp[i], '=') != NULL)
			ft_putstr_fd("\"\"", 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
}

int ft_export(char **argv, char ***envp, t_gc **gc, t_gc **lst, int *boll)
{
	int g;
	int i;
	int j;
	int bol;
	char *tmp;
	int status;

	status = 0;
	g = ft_strlen_double(argv);
	if (g == 1)
		return (print_exported_variables(*envp, gc, *boll), 0);
	i = 1;
	if (ft_strcmp(get_key(argv[i], gc), "PATH") == 0 && boll != 0)
		*boll = 0;
	while (argv[i])
	{	
		if (get_key(argv[i], gc) == NULL)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			status = 1;
		}
		else
		{
			j = 0;
			bol = 0;
			while ((*envp)[j] != NULL)
			{
				if (ft_strcmp(get_key((*envp)[j], gc), get_key(argv[i], gc)) == 0)
				{
					bol = 1;
					if (ft_strchr(argv[i], '=') == NULL)
						break;
					if (ft_strchr(argv[i], '+') != NULL)
					{
						tmp = get_value(argv[i], gc);
						argv[i] = ft_strjoin(get_key(argv[i], gc), "=", gc);
						argv[i] = ft_strjoin(argv[i], tmp, lst);
						(*envp)[j] = argv[i];
					}
					else
						(*envp)[j] = ft_strdup(argv[i], lst);
					break;
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
