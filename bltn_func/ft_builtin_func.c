/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 11:02:09 by relamine          #+#    #+#             */
/*   Updated: 2024/08/06 19:04:41 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_is_bultin(char *argv, char **builtins)
{
	int i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strcmp(argv, builtins[i]))
			return (i);
		i++;
	}
	return (-1);
}

static int execute_bltncmd(int is_bultin, t_cmd *cmd, char ***envpv, t_gc **gc, t_gc **lst)
{
	char **argv;

	argv = cmd->args;
	if (is_bultin == 0)
		return (pwd());
	else if (is_bultin == 1)
		return (env(*envpv, gc, *cmd->flag_display_env));
	else if (is_bultin == 2)
		return (cd(argv, envpv, gc, lst));
	else if (is_bultin ==  3)
		return (ft_export(argv, envpv, gc, lst, cmd->flag_display_env));
	else if (is_bultin == 4)
		return (unset(argv, envpv, gc, lst));
	else if(is_bultin ==  5)
		exit_0(1, ft_strlen_double(argv + 1), argv);
	else if (is_bultin == 6)
		return (echo(ft_strlen_double(argv),argv, envpv, lst));
	return (ft_execute(cmd, envpv, gc, lst));
}
int ft_builtin_func(t_cmd *cmd, char ***envpv, t_gc **gc, t_gc **lst)
{
	int i;
	char **argv;
	int is_bultin;
	const char *builtins[8] = {"pwd", "env", "cd", "export", "unset", "exit", "echo", NULL};

	i = 0;
	argv = cmd->args;
	if (argv == NULL || argv[i] == NULL)
		return (ft_export_anything("_=", gc, lst, envpv), 0);

	if (cmd->red_in_fd > 0)
		dup2(cmd->red_in_fd, 0);
	if (cmd->red_out_fd > 1)
		dup2(cmd->red_out_fd, 1);
	
	is_bultin = ft_is_bultin(argv[i], (char **)builtins);
	if (*cmd->flag_pipe)
		ft_export_anything("_=", gc, lst, envpv);
	if (!*cmd->flag_pipe && ft_strlen_double(argv) && is_bultin != -1)
		ft_export_(argv, envpv, gc, lst);
	return (execute_bltncmd(is_bultin, cmd, envpv, gc, lst));
}
