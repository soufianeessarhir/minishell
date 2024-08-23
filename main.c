/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/23 17:19:37 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rrl_nr_helpr_f2(t_norm_rll *helper)
{
	helper->lgc_norm.l_gc = &helper->l_gc;
	helper->lgc_norm.lst = helper->lst;
	helper->lgc_norm.bol = helper->bol;
}

void	readline_loop_hellper2(t_norm_rll *helper)
{
	if (g_a.exitstatus_singnal == 1)
	{
		ft_export_status(1, &helper->env, &helper->l_gc, helper->lst);
		g_a.exitstatus_singnal = 0;
	}
	intit_env_list(&helper->env_lst, helper->env, helper->lst);
	if (*(helper->line)[0] != '\0' && !white_spaces(*(helper->line)))
	{
		add_history(*(helper->line));
		rll_nr_helpr_f(helper);
		if (parsing_part(&helper->help, &helper->env_lst, &helper->l_gc,
				&helper->cmd) || g_a.stphedorc_insgin == 2)
		{
			if (g_a.stphedorc_insgin == 2)
				rll_helper2();
			g_a.stphedorc_insgin = 0;
			return (free_nr_rl_vars(&helper->cmd, &helper->env_lst,
					&helper->l_gc, helper->line), (void)0);
		}
		rrl_nr_helpr_f2(helper);
		main_execute(helper->cmd, helper->env_lst,
			helper->lgc_norm, &helper->env);
	}
	free_nr_rl_vars(&helper->cmd, &helper->env_lst,
		&helper->l_gc, helper->line);
}

void	readline_loop_hellper(t_norm_rll *helper)
{
	while (1)
	{
		setting_term(&helper->term, &helper->term_orig);
		*(helper->line)
			= readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
		if (!*(helper->line))
		{
			write(0, "exit\n", 5);
			intit_env_list(&helper->env_lst, helper->env, helper->lst);
			helper->exit_s = my_getenv("@exitstatus", helper->env_lst);
			helper->status = 0;
			if (g_a.exitstatus_singnal == 1)
				rll_helper1(&helper->status, &g_a.exitstatus_singnal);
			else if (helper->exit_s)
				helper->status = ft_atoi(helper->exit_s);
			return (ft_free(&helper->l_gc),
				ft_free(helper->lst), exit(helper->status));
		}
		readline_loop_hellper2(helper);
		tcsetattr(STDIN_FILENO, TCSANOW, &helper->term_orig);
	}
}

void	readline_loop(char **line, t_gc **lst, char **env)
{
	t_norm_rll	help_rll;

	init_rn_rll(&help_rll);
	help_rll.bol = setup_env_and_path(&env, lst, &help_rll.l_gc);
	check_and_export_status(&env, &help_rll.l_gc, lst);
	help_rll.env = env;
	help_rll.lst = lst;
	help_rll.line = line;
	readline_loop_hellper(&help_rll);
}

int	main(int ac, char **av, char **env)
{
	t_gc			*lst;
	char			*line;

	lst = NULL;
	if (ac != 1)
		return (printf("Usage: %s\n", av[0]), 1);
	rl_catch_signals = 0;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigint);
	readline_loop(&line, &lst, env);
	ft_free(&lst);
	return (0);
}
