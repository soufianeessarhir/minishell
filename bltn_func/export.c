/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 06:30:00 by relamine          #+#    #+#             */
/*   Updated: 2024/08/29 05:09:31 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	handle_existing_key(char *arg, char ***envp, t_gc **gc, t_gc **lst)
{
	int		bol;
	int		j;

	initialize(&j, &bol);
	while ((*envp)[j] != NULL)
	{
		if (ft_strcmp(get_key((*envp)[j], gc), get_key(arg, gc)) == 0)
		{
			bol = 1;
			if (ft_strchr(arg, '=') == NULL)
				break ;
			if (ft_strchr(arg, '+') != NULL)
			{
				arg = get_value(arg, gc);
				if (ft_strchr((*envp)[j], '=') == NULL)
					arg = ft_strjoin("=", arg, lst);
				(*envp)[j] = ft_strjoin((*envp)[j], arg, lst);
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

static void	handle_new_key(char *arg, char ***envp, t_gc **gc, t_gc **lst)
{
	char	*tmp;

	if (ft_strchr(arg, '+') != NULL)
	{
		tmp = get_value(arg, gc);
		arg = ft_strjoin(get_key(arg, gc), "=", gc);
		arg = ft_strjoin(arg, tmp, lst);
	}
	combine_env_and_args(envp, arg, lst);
}

int	ft_export(char **argv, char ***envp, t_norm n)
{
	int		i;
	int		status;

	status = 0;
	i = 1;
	if (ft_strlen_double(argv) == 1)
		return (print_exported_variables(*envp, n.l_gc, *n.bol2), 0);
	if (ft_strcmp(get_key(argv[i], n.l_gc), "PATH") == 0 && n.bol2 != 0)
		*n.bol2 = 0;
	while (argv[i])
	{
		if (get_key(argv[i], n.l_gc) == NULL
			|| ft_isonlydigit(get_key(argv[i], n.l_gc)))
			status = print_export_error(argv[i]);
		else
		{
			if (!handle_existing_key(argv[i], envp, n.l_gc, n.lst))
				handle_new_key(argv[i], envp, n.l_gc, n.lst);
		}
		i++;
	}
	return (status);
}
