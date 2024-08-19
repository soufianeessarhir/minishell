/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/19 16:26:13 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_part(t_help *help, t_env **env_lst, t_gc **l_gc, t_cmd **cmd)
{
	t_token	*token_lst;

	token_lst = NULL;
	if (sp_uq_handling(help->line))
		return (1);
	ft_tokinize(help->line, &token_lst, l_gc);
	if (syntax_error(&token_lst, l_gc, *env_lst))
		return (ft_export_status(258, help->env, l_gc, help->lst), 1);
	her_doc_handling(&token_lst, l_gc, *env_lst);
	env_handling(&token_lst, *env_lst, l_gc);
	init_cmd(cmd, token_lst, l_gc);
	if (open_redirection(cmd, l_gc))
		return (ft_export_status(1, help->env, l_gc, help->lst), 1);
	return (0);
}

void readline_loop(char **line, t_gc **lst, char **env) 
{
	t_env	*env_lst;
	t_gc	*l_gc;
	t_cmd	*cmd;
	char	**tmp_env;
	int		bol;
	t_help	help;
	t_norm	lgc_norm;
	char	*exit_s;
	int		status;

	l_gc = NULL;
	env_lst = NULL;
	cmd = NULL;
	tmp_env = NULL;
	bol = setup_env_and_path(&env, lst, &l_gc);
	check_and_export_status(&env, &l_gc, lst);
	while (1)
	{
		g_a.exitstatus_singnal = 0;
		*line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
		if (!*line)
		{
			write(0, "exit\n", 5);
			intit_env_list(&env_lst, env, lst);
			exit_s = my_getenv("@exitstatus", env_lst);
			status = 0;
			if (g_a.exitstatus_singnal == 1)
			{
				status = 1;
				g_a.exitstatus_singnal = 0;
			}
			else if (exit_s)
				status = ft_atoi(exit_s);
			exit(status);
		}
		if (g_a.exitstatus_singnal == 1)
		{
			ft_export_status(1, &env, &l_gc, lst);
			g_a.exitstatus_singnal = 0;
		}
		intit_env_list(&env_lst, env, lst);
		if (*line[0] != '\0')
		{
			add_history(*line);
			help.line = *line;
			help.env = &env;
			help.lst = lst;
			if (parsing_part(&help, &env_lst, &l_gc, &cmd)
				|| g_a.stphedorc_insgin == 2)
			{
				if (g_a.stphedorc_insgin == 2)
					dup2(1, 0);
				g_a.stphedorc_insgin = 0;
				free(*line);
				*line = NULL;
				ft_free(&l_gc);
				cmd = NULL;
				env_lst = NULL;
				continue ;
			}
			lgc_norm.l_gc = &l_gc;
			lgc_norm.lst = lst;
			lgc_norm.bol = bol;
			main_execute(cmd, env_lst, lgc_norm, &env);
			free(*line);
			*line = NULL;
			ft_free(&l_gc);
			cmd = NULL;
			env_lst = NULL;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	struct termios	term, term_orig;
	t_gc			*lst;
	char			*line;

	tcgetattr(STDIN_FILENO, &term);
	term_orig = term;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	lst = NULL;
	if (ac != 1)
		return (printf("Usage: %s\n", av[0]), 1);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	readline_loop(&line, &lst, env);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_orig);
	ft_free(&lst);
	return (0);
}
