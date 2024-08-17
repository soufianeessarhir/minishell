/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/08/17 11:32:15 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int handle_existing_key(char *arg, char ***envp, t_gc **gc, t_gc **lst)
{
    int bol;
    int j;
    char *tmp;

	j = 0;
	bol = 0;
	while ((*envp)[j] != NULL)
	{
		if (ft_strcmp(get_key((*envp)[j], gc), get_key(arg, gc)) == 0)
		{
			if (ft_strchr(arg, '=') == NULL)
				break ;
			if (ft_strchr(arg, '+') != NULL)
			{
				tmp = get_value(arg, gc);
				(*envp)[j] = ft_strjoin((*envp)[j], tmp, lst);
			}
			else
				(*envp)[j] = ft_strdup(arg, lst);
			break ;
		}
		j++;
	}
    return (bol);
}

static void	combine_env_and_args(char ***envp, char *argv, t_gc **lst)
{
	size_t	env_count;
	char	**new_env;
	size_t	i;

	env_count = ft_strlen_double(*envp);
	new_env = ft_malloc(sizeof(char *) * (env_count + 2), lst);
	i = 0;
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
static void handle_new_key(char *arg, char ***envp, t_gc **gc, t_gc **lst) {
    char *tmp;
    
    if (ft_strchr(arg, '+') != NULL) {
        tmp = get_value(arg, gc);
        arg = ft_strjoin(get_key(arg, gc), "=", gc);
        arg = ft_strjoin(arg, tmp, lst);
    }
    combine_env_and_args(envp, arg, lst);
}

int	ft_export(char **argv, char ***envp, t_gc **gc, t_gc **lst, int *boll)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	if (ft_strlen_double(argv) == 1)
		return (print_exported_variables(*envp, gc, *boll), 0);
	if (ft_strcmp(get_key(argv[i], gc), "PATH") == 0 && boll != 0)
		*boll = 0;
	while (argv[i])
	{
		if (get_key(argv[i], gc) == NULL || ft_isonlydigit(get_key(argv[i], gc)))
			status = print_export_error(argv[i]);
		else
		{
			if (!handle_existing_key(argv[i], envp, gc, lst))
				handle_new_key(argv[i], envp, gc, lst);
		}
		i++;
	}
	return (status);
}
