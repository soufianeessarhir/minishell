/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_to_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 10:55:21 by relamine          #+#    #+#             */
/*   Updated: 2024/08/22 17:10:57 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_pwd(char *which, char ***envp, t_gc **l_gc, t_gc **lst)
{
	char	**args;
	t_norm	lst_n;

	lst_n.l_gc = l_gc;
	lst_n.lst = lst;
	lst_n.bol2 = 0;
	args = ft_malloc(sizeof(char *) * 3, l_gc);
	args[0] = ft_strdup("export", l_gc);
	args[1] = ft_strjoin(which, getcwd(NULL, 0), l_gc);
	args[2] = NULL;
	ft_export(args, envp, lst_n);
}

void	ft_export_(char **argv, char ***envpv, t_gc **gc, t_gc **lst)
{
	int		q;
	char	**tmp;
	char	*arg;
	t_norm	lst_n;
	char	*tmp_arg;

	lst_n.l_gc = gc;
	lst_n.lst = lst;
	lst_n.bol2 = 0;
	q = ft_strlen_double(argv) - 1;
	tmp_arg = argv[q];
	if (strcmp(argv[0], "export") == 0 && get_key(tmp_arg, gc))
		tmp_arg = get_key(argv[q], gc);
	tmp = (char **)ft_malloc(sizeof(char *) * 3, lst);
	tmp[0] = ft_strdup("export", gc);
	arg = ft_strdup(tmp_arg, gc);
	tmp[1] = ft_strjoin("_=", arg, gc);
	tmp[2] = NULL;
	ft_export(tmp, envpv, lst_n);
}

void	export_shelvl(char ***envp, t_gc **l_gc, t_gc **lst, t_env *env_lst)
{
	char	*tmp;
	char	**shelvl;
	char	*num_shlvl;
	int		i;
	t_norm	lst_n;

	lst_n.l_gc = l_gc;
	lst_n.lst = lst;
	lst_n.bol2 = 0;
	num_shlvl = my_getenv("SHLVL", env_lst);
	if (!num_shlvl)
		num_shlvl = "0";
	i = ft_atoi(num_shlvl);
	if (i == 0 || i >= 10240)
		i = 1;
	else if (i < 0)
		i = 0;
	else
		i++;
	tmp = ft_strjoin("SHLVL=", ft_itoa(i, l_gc), l_gc);
	shelvl = ft_malloc(sizeof(char *) * 3, l_gc);
	shelvl[0] = ft_strdup("export", l_gc);
	shelvl[1] = tmp;
	shelvl[2] = NULL;
	ft_export(shelvl, envp, lst_n);
}

void	ft_export_anything(char *argv, t_gc **l_gc, t_gc **lst, char ***env)
{
	char	**tmp;
	t_norm	lst_n;

	lst_n.l_gc = l_gc;
	lst_n.lst = lst;
	lst_n.bol2 = 0;
	tmp = ft_malloc(sizeof(char *) * 3, lst);
	tmp[0] = ft_strdup("export", l_gc);
	tmp[1] = ft_strdup(argv, l_gc);
	tmp[2] = NULL;
	ft_export(tmp, env, lst_n);
}

void	system_export_config(char *key, char *value, char ***envp, t_gc **lst)
{
	size_t	env_count;
	char	**new_env;
	int		i;

	i = 0;
	env_count = ft_strlen_double(*envp);
	new_env = ft_malloc(sizeof(char *) * (env_count + 2), lst);
	while ((*envp)[i])
	{
		new_env[i] = ft_strdup((*envp)[i], lst);
		i++;
	}
	new_env[i] = ft_strjoin(key, value, lst);
	new_env[i + 1] = NULL;
	*envp = new_env;
}
