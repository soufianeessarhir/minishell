/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/08/20 08:18:13 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_builtin(char *argv, char **builtins)
{
	int	i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(argv, builtins[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int	execute_bltncmd(int is_builtin,
	t_cmd *cmd,	char ***envpv, t_norm lst_n)
{
	char	**argv;
	t_gc	**gc;
	t_gc	**lst;

	gc = lst_n.l_gc;
	lst = lst_n.lst;
	lst_n.bol2 = cmd->flag_display_env;
	argv = cmd->args;
	if (is_builtin == 0)
		return (pwd());
	else if (is_builtin == 1)
		return (env(*envpv, gc, *cmd->flag_display_env));
	else if (is_builtin == 2)
		return (cd(argv, envpv, gc, lst));
	else if (is_builtin == 3)
		return (ft_export(argv, envpv, lst_n));
	else if (is_builtin == 4)
		return (unset(argv, envpv, gc, lst));
	else if (is_builtin == 5)
		return (exit_0(ft_strlen_double(argv + 1), argv, cmd->flag_pipe, lst_n));
	else if (is_builtin == 6)
		return (echo(ft_strlen_double(argv), argv));
	return (ft_execute(cmd, envpv, lst_n));
}

static char	**initialize_builtins(void)
{
	static char	*builtins[8];

	builtins[0] = "pwd";
	builtins[1] = "env";
	builtins[2] = "cd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "exit";
	builtins[6] = "echo";
	builtins[7] = NULL;
	return (builtins);
}

int	ft_builtin_func(t_cmd *cmd, char ***envpv, t_gc **gc, t_gc **lst)
{
	int			i;
	char		**argv;
	char		**builtins;
	int			status;
	t_norm		norm_bag;

	i = 0;
	builtins = initialize_builtins();
	norm_bag.l_gc = gc;
	norm_bag.lst = lst;
	argv = cmd->args;
	if (argv == NULL || argv[i] == NULL)
		return (0);
	norm_bag.bol = ft_is_builtin(argv[i], (char **)builtins);
	if (!*cmd->flag_pipe && ft_strlen_double(argv) && norm_bag.bol != 1)
		ft_export_(argv, envpv, gc, lst);
	if (norm_bag.bol == 1)
		ft_export_anything("_=/usr/bin/env", gc, lst, envpv);
	status = execute_bltncmd(norm_bag.bol, cmd, envpv, norm_bag);
	if (norm_bag.bol == 1)
		ft_export_anything("_=env", gc, lst, envpv);
	return (status);
}
