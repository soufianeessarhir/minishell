/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 19:16:48 by relamine          #+#    #+#             */
/*   Updated: 2024/08/26 02:13:33 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_pipes(t_shell_vars *vars, t_cmd *cmd)
{
	vars->num_pipe = 0;
	vars->tmp = cmd;
	while (vars->tmp && vars->tmp->next)
	{
		vars->num_pipe += 1;
		vars->tmp = vars->tmp->next;
	}
	vars->pipes_fds = ft_malloc(sizeof(int) * vars->num_pipe * 2, vars->l_gc);
	vars->i = 0;
	while (vars->i < vars->num_pipe)
	{
		vars->flag_pipe = 1;
		if (pipe(&vars->pipes_fds[vars->i * 2]) == -1)
		{
			perror("pipe");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		vars->i++;
	}
	vars->tmp = cmd;
}

int	fork_and_manage_process(t_shell_vars *vars)
{
	vars->childpid = fork();
	if (vars->childpid == -1)
	{
		perror("fork");
		kill(vars->firstchild_pid, SIGKILL);
		return (1);
	}
	else if (vars->childpid > 0)
	{
		if (!vars->tmp->next)
			vars->last_childpid = vars->childpid;
		if (vars->cmd_pipe == 0)
			vars->firstchild_pid = vars->childpid;
	}
	return (0);
}

static void	wait_for_processes(t_shell_vars *vars, char ***env)
{
	vars->i = 0;
	g_a.stpsignal_inparent = 1;
	while (vars->i <= vars->num_pipe)
	{
		vars->childpid_tmp = wait(&vars->status);
		if (vars->childpid_tmp == vars->last_childpid)
		{
			if (WIFSIGNALED(vars->status))
			{
				vars->status = 128 + WTERMSIG(vars->status);
				ft_export_status(vars->status, env, vars->l_gc, vars->lst);
			}
			else
				ft_export_status(WEXITSTATUS(vars->status),
					env, vars->l_gc, vars->lst);
		}
		vars->i++;
	}
}

void	handle_pipe_status(t_shell_vars *vars, char ***env)
{
	if (vars->flag_pipe)
	{
		vars->i = 0;
		while (vars->i < vars->num_pipe * 2)
		{
			close(vars->pipes_fds[vars->i]);
			vars->i++;
		}
		wait_for_processes(vars, env);
		if (vars->status == 130)
			printf("\n");
		if (vars->status == 131)
			printf("Quit: 3\n");
		if (vars->childpid == -1)
			ft_export_status(1, env, vars->l_gc, vars->lst);
		ft_export_anything("_=", vars->l_gc, vars->lst, env);
	}
}

int	advance_to_next_command(t_shell_vars *vars)
{
	if (vars->l == 2)
		return (1);
	vars->tmp = vars->tmp->next;
	if (vars->tmp)
		vars->cmd_pipe++;
	else if (vars->l == 1)
	{
		vars->l = 2;
		vars->tmp = vars->path_program;
		vars->cmd_pipe = 0;
	}
	return (0);
}
