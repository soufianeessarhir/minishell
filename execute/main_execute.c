/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:13:18 by relamine          #+#    #+#             */
/*   Updated: 2024/08/26 03:21:21 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_shell_vars	init_shell_vars(t_cmd *cmd, t_norm l_norm)
{
	t_shell_vars	vars;

	vars.tmp = cmd;
	vars.pipes_fds = NULL;
	vars.i = 0;
	vars.flag_pipe = 0;
	vars.num_pipe = 0;
	vars.cmd_pipe = 0;
	vars.tmp_cmd_pipe = 0;
	vars.last_childpid = 0;
	vars.firstchild_pid = 0;
	vars.in_fd = -1;
	vars.out_fd = -1;
	vars.status = 0;
	vars.childpid_tmp = 0;
	vars.stexit = 0;
	vars.childpid = -1;
	vars.bol = l_norm.bol;
	vars.l = 0;
	vars.path_program = NULL;
	vars.l_gc = l_norm.l_gc;
	vars.lst = l_norm.lst;
	return (vars);
}

static void	handle_inout_redirection(t_shell_vars *vars)
{
	if (vars->tmp->red_in_fd > 0)
	{
		vars->in_fd = dup(STDIN_FILENO);
		if (dup2(vars->tmp->red_in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		close(vars->tmp->red_in_fd);
	}
	if (vars->tmp->red_out_fd > 1)
	{
		vars->out_fd = dup(STDOUT_FILENO);
		if (dup2(vars->tmp->red_out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (ft_free(vars->l_gc), ft_free(vars->lst), exit(1));
		}
		close(vars->tmp->red_out_fd);
	}
}

static void	handle_redirections_and_execute(t_shell_vars *vars, char ***env)
{
	handle_inout_redirection(vars);
	vars->stexit = ft_builtin_func(vars->tmp, env, vars->l_gc, vars->lst);
	if (vars->tmp->red_in_fd > 0)
	{
		if (dup2(vars->in_fd, STDIN_FILENO) == -1)
		{
			perror("dup2");
			ft_free(vars->l_gc);
			ft_free(vars->lst);
			exit(1);
		}
		close(vars->in_fd);
	}
	if (vars->tmp->red_out_fd > 1)
	{
		if (dup2(vars->out_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			ft_free(vars->l_gc);
			ft_free(vars->lst);
			exit(1);
		}
		close(vars->out_fd);
	}
	ft_export_status(vars->stexit, env, vars->l_gc, vars->lst);
}

static int	check_and_update_path_program(t_shell_vars *vars)
{
	if (vars->l < 1 && vars->tmp->num_cmd == 0
		&& ft_strnstr(vars->tmp->args[0], "minishell",
			ft_strlen(vars->tmp->args[0])))
	{
		vars->l = 1;
		vars->path_program = vars->tmp;
		vars->tmp = vars->tmp->next;
		vars->cmd_pipe++;
		return (1);
	}
	return (0);
}

void	main_execute(t_cmd *cmd, t_env *env_lst, t_norm l_norm, char ***env)
{
	t_shell_vars	vars;

	vars = init_shell_vars(cmd, l_norm);
	setup_pipes(&vars, cmd);
	while (vars.tmp)
	{
		initialize_cmd_vars(&vars, env_lst);
		if (vars.flag_pipe)
		{
			if (check_and_update_path_program(&vars))
				continue ;
			if (fork_and_manage_process(&vars))
				break ;
			handle_child_process(&vars, env);
		}
		else
			handle_redirections_and_execute(&vars, env);
		if (advance_to_next_command(&vars))
			break ;
	}
	handle_pipe_status(&vars, env);
	close_redirection_pipe(&vars, cmd);
}
