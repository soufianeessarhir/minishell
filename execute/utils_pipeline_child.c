/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline_child.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 20:25:37 by relamine          #+#    #+#             */
/*   Updated: 2024/08/20 08:42:08 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	handle_pipes(t_shell_vars *vars)
{
	if (vars->tmp->next && vars->l != 2 && vars->tmp->red_out_fd == 1)
	{
		if (dup2(vars->pipes_fds[(vars->cmd_pipe * 2) + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
	}
	if (vars->cmd_pipe > 0 && vars->tmp->red_in_fd == 0)
	{
		if (dup2(vars->pipes_fds[(vars->cmd_pipe - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
	}
}

static void	handle_redirections_pipe(t_shell_vars *vars)
{
	if (vars->tmp->red_in_fd > 0)
	{
		vars->in_fd = dup(0);
		if (dup2(vars->tmp->red_in_fd, 0) < 0)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		close(vars->tmp->red_in_fd);
	}
	if (vars->tmp->red_out_fd > 1)
	{
		vars->out_fd = dup(1);
		if (dup2(vars->tmp->red_out_fd, 1) < 0)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		close(vars->tmp->red_out_fd);
	}
	handle_pipes(vars);
}

static void	execute_command_pipe(t_shell_vars *vars, char ***env)
{
	vars->i = 0;
	while (vars->i < vars->num_pipe * 2)
	{
		close(vars->pipes_fds[vars->i]);
		vars->i++;
	}
	vars->stexit = ft_builtin_func(vars->tmp, env, vars->l_gc, vars->lst);
	return (ft_free(vars->l_gc), ft_free(vars->lst), exit(vars->stexit));
}

void	handle_child_process(t_shell_vars *vars, char ***env)
{
	if (vars->childpid == 0)
	{
		if (vars->tmp->exit_status == 1)
		{
			vars->i = 0;
			while (vars->i < vars->num_pipe * 2)
			{
				close(vars->pipes_fds[vars->i]);
				vars->i++;
			}
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		handle_redirections_pipe(vars);
		execute_command_pipe(vars, env);
	}
}

void	initialize_shell_environment(char *path_program, t_gc **l_gc,
	t_gc **lst, char ***env)
{
	char	*tmp;

	tmp = "PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin";
	ft_export_anything("SHLVL=1", l_gc, lst, env);
	ft_export_anything(tmp, l_gc, lst, env);
	ft_export_anything(ft_strjoin("_=", path_program, lst), l_gc, lst, env);
	system_export_config("@hidden_PATH=", "1", env, lst);
}
