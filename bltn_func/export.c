/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/07/17 05:57:08 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *get_key(char *str)
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
	key = ft_substr(str, 0, i);
	return (key);
}
char *get_value(char *str)
{
	int i;
	char *value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0' || str[i + 1] == '\0')
		return (NULL);
	i++;
	value = ft_strdup(str + i);
	if (value == NULL)
		return (NULL);
	return (value);
}

// Function to combine environment variables and arguments
void combine_env_and_args(char ***envp, char *argv)
{
    size_t env_count = ft_strlen_double(*envp);
    char **new_env = malloc(sizeof(char *) * (env_count + 2));
    // Copy existing environment variables
	size_t i = 0;

	while (i < env_count)
	{
		new_env[i] = ft_strdup((*envp)[i]);
		i++;
	}
    
  	new_env[i] = ft_strdup(argv);
	i++;

	new_env[i] = NULL;
    *envp = new_env;
	i=0;
}

// Function to print exported environment variables
void print_exported_variables(char **envp) {
    int i = 0;
    while (envp[i] != NULL)
	{
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(envp[i], 1);
		if (get_value(envp[i]) == NULL && strchr(envp[i], '=') != NULL)
			ft_putstr_fd("\"\"", 1);
        ft_putstr_fd("\n", 1);
        i++;
    }
}

void ft_export(char **argv, char ***envp)
{
	int g;
	int i;
	int j;
	int bol;
	char *tmp;

	g = ft_strlen_double(argv);
	if (g == 1)
		return (print_exported_variables(*envp));
	i = 1;
	while (argv[i])
	{	
		if (get_key(argv[i]) == NULL)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
		{
			j = 0;
			bol = 0;
			while ((*envp)[j] != NULL)
			{
				if (ft_strcmp(get_key((*envp)[j]), get_key(argv[i])) == 0)
				{
					bol = 1;
					if (ft_strchr(argv[i], '=') == NULL)
						break;
					if (ft_strchr(argv[i], '+') != NULL)
					{
						tmp = get_value(argv[i]);
						argv[i] = ft_strjoin(get_key(argv[i]), "=");
						argv[i] = ft_strjoin(argv[i], tmp);
						(*envp)[j] = argv[i];
					}
					else
						(*envp)[j] = ft_strdup(argv[i]);
					break;
				}
				j++;
			}
			if (bol == 0)
			{
				if (ft_strchr(argv[i], '+') != NULL)
				{
					tmp = get_value(argv[i]);
					argv[i] = ft_strjoin(get_key(argv[i]), "=");
					argv[i] = ft_strjoin(argv[i], tmp);
					combine_env_and_args(envp, argv[i]);
				}
				else
					combine_env_and_args(envp, argv[i]);
			}
		}
		i++;
	}
	return ;
}
