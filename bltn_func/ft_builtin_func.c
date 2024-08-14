/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/08/14 09:04:31 by relamine         ###   ########.fr       */
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

static int	execute_bltncmd(int is_builtin, t_cmd *cmd, char ***envpv, t_gc **gc, t_gc **lst)
{
	char	**argv;

	argv = cmd->args;
	if (is_builtin == 0)
		return (pwd());
	else if (is_builtin == 1)
		return (env(*envpv, gc, *cmd->flag_display_env));
	else if (is_builtin == 2)
		return (cd(argv, envpv, gc, lst));
	else if (is_builtin == 3)
		return (ft_export(argv, envpv, gc, lst, cmd->flag_display_env));
	else if (is_builtin == 4)
		return (unset(argv, envpv, gc, lst));
	else if (is_builtin == 5)
		return (exit_0(1, ft_strlen_double(argv + 1), argv, cmd->flag_pipe));
	else if (is_builtin == 6)
		return (echo(ft_strlen_double(argv), argv, envpv, lst));
	return (ft_execute(cmd, envpv, gc, lst));
}
int	ft_builtin_func(t_cmd *cmd, char ***envpv, t_gc **gc, t_gc **lst)
{
	int			i;
	char		**argv;
	int			is_builtin;
	const char	*builtins[8] = {"pwd", "env", "cd", "export", "unset", "exit", "echo", NULL};
	int			status;

	i = 0;
	argv = cmd->args;
	if (argv == NULL || argv[i] == NULL)
		return (0);
	is_builtin = ft_is_builtin(argv[i], (char **)builtins);
	if (!*cmd->flag_pipe && ft_strlen_double(argv) && is_builtin != 1)
		ft_export_(argv, envpv, gc, lst);
	if (is_builtin == 1 && !*cmd->flag_pipe)
		ft_export_anything("_=/usr/bin/env", gc, lst, envpv);
	status = execute_bltncmd(is_builtin, cmd, envpv, gc, lst);
	if (is_builtin == 1 && !*cmd->flag_pipe)
		ft_export_anything("_=env", gc, lst, envpv);
	return (status);
}
