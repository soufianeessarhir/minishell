/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/16 10:52:29 by sessarhi         ###   ########.fr       */
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
	char	**exitstatus;
	char	**tmp_env;
	int		stexit;
	int		flag_pipe;
	int		bol;
	t_help	help;
	int		childpid;

	childpid = -1;
	l_gc = NULL;
	stexit = -9999;
	env_lst = NULL;
	cmd = NULL;
	exitstatus = NULL;
	tmp_env = NULL;

	bol = setup_env_and_path(&env, lst, &l_gc);
	check_and_export_status(&env, &l_gc, lst);
	
    while (1) {
		flag_pipe = 0;
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(g_a.exitstatus_singnal);
        }
		if (g_a.exitstatus_singnal == 1)
		{
			ft_export_status(g_a.exitstatus_singnal, &env, &l_gc, lst);
			g_a.exitstatus_singnal = 0;
		}
		if (bol == 1)
			printf("Error: malloc\n");
    	intit_env_list(&env_lst, env, lst);
        if (*line[0] != '\0')
		{	
			add_history(*line);
			help.line = *line;
			help.env = &env;
			help.lst = lst;
			if (parsing_part(&help, &env_lst, &l_gc, &cmd) || g_a.stphedorc_insgin == 2)
			{
				if (g_a.stphedorc_insgin == 2)
					dup2(1, 0);
				g_a.stphedorc_insgin = 0;
				free(*line);
				*line = NULL;
				ft_free(&l_gc);
				cmd = NULL;
				env_lst = NULL;
				continue;
			}
			t_cmd *tmp = cmd;
            // for (t_cmd *tmp = cmd; tmp; tmp = tmp->next)
			// {
			// 	for (int i = 0; tmp->args[i]; i++)
			// 		printf("args: %s\n", tmp->args[i]);
			// 	for (t_redir *tmp2 = tmp->rd; tmp2; tmp2 = tmp2->next)
			// 	printf("redir: %s\n", tmp2->redio);
			// }
			int num_pipe;

			num_pipe = 0;
			while (tmp && tmp->next)
			{
				num_pipe += 1;
				tmp = tmp->next;
			}

			// create pipes
			tmp = cmd;
			int *pipes_fds;
			int i;
	
			pipes_fds = ft_malloc(sizeof(int) * num_pipe * 2, &l_gc);
			i = 0;
			while (i < num_pipe)
			{
				flag_pipe = 1;
				if (pipe(&pipes_fds[i * 2]) == -1)
				{
					perror("pipe");
					exit(1);
				}
				i++;
			}
			
			int cmd_pipe;
			int tmp_cmd_pipe;
			int l = 0;
			t_cmd *path_program;


			cmd_pipe = 0;
			path_program = NULL;
			tmp_cmd_pipe =0;
			int last_childpid;

			last_childpid = 0;
			int firstchild_pid = 0;
			while (tmp)
			{
				tmp->flag_pipe = &flag_pipe;
				tmp->flag_display_env = &bol;
				tmp->num_cmd = cmd_pipe;
				tmp->path_of_program =  my_getenv("@path_of_program", env_lst);
				
				
				if (flag_pipe)
				{
					flag_pipe = 1;
					if (l < 1 && tmp->num_cmd == 0 && ft_strnstr(tmp->args[0], "./minishell", ft_strlen(tmp->args[0])))
					{
						l = 1;
						path_program = tmp;
						tmp = tmp->next;
						cmd_pipe++;
						continue;
					}
					childpid = fork();
					if (childpid == -1)
					{
						perror("fork");
						kill(firstchild_pid, SIGKILL);
						break;
					}
					if (childpid > 0)
					{
						if (!tmp->next)
							last_childpid = childpid;
						if (cmd_pipe == 0)
							firstchild_pid = childpid;
					}
					if (childpid == 0)
					{
						if (tmp->exit_status == 1)
						{
							i = 0;
							while (i < num_pipe * 2)
							{
								close(pipes_fds[i]);
								i++;
							}
							exit(1);
						}
						int in_fd = -1;
						int out_fd = -1;

						if (tmp->red_in_fd > 0)
						{
							in_fd = dup(0);
							dup2(tmp->red_in_fd, 0);
							close(tmp->red_in_fd);
						}
						if (tmp->red_out_fd > 1)
						{
							out_fd = dup(1);
							dup2(tmp->red_out_fd, 1);
							close(tmp->red_out_fd);
						}
						
						// if not the last command
						if (tmp->next && l != 2 && tmp->red_out_fd == 1)
						{
							if (dup2(pipes_fds[(cmd_pipe * 2) + 1], STDOUT_FILENO) < 0)
							{
								perror("dup2");
								exit(1);
							}
						}	
				// if not the first command get input from the previous command
						if (cmd_pipe > 0 && tmp->red_in_fd == 0)
						{
							if (dup2(pipes_fds[(cmd_pipe - 1) * 2], STDIN_FILENO) < 0)
							{
								perror("dup2");
								exit(1);
							}
						}
						i = 0;
						while (i < num_pipe * 2)
						{
							close(pipes_fds[i]);
							i++;
						}
						stexit = ft_builtin_func(tmp, &env, &l_gc, lst);
						exit(stexit);
					}
				}
				else 
				{					
				    int in_fd = -1;
					int out_fd = -1;

					if (tmp->red_in_fd > 0)
					{
						in_fd = dup(0);
						dup2(tmp->red_in_fd, 0);
						close(tmp->red_in_fd);
					}
					if (tmp->red_out_fd > 1)
					{
						out_fd = dup(1);
						dup2(tmp->red_out_fd, 1);
						close(tmp->red_out_fd);
					}
					stexit = ft_builtin_func(tmp, &env, &l_gc, lst);
					if (tmp->red_in_fd > 0)
					{
						dup2(in_fd, 0);
						close(in_fd);
					}
					if (tmp->red_out_fd > 1)
					{
						dup2(out_fd, 1);
						close(out_fd);
					}
					ft_export_status(stexit, &env, &l_gc, lst);
				}
				if (l == 2)
					break ;
				tmp = tmp->next;
				if (tmp)
					cmd_pipe++;
				if (!tmp && l == 1)
				{
					l = 2;
					tmp = path_program;
					cmd_pipe = 0;
				}
			}
			if (flag_pipe)
			{
				int status;
				ft_export_status(0, &env, &l_gc, lst);
				i = 0;
				while (i < num_pipe * 2)
				{
					close(pipes_fds[i]);
					i++;
				}
				i = 0;
				while (i <= num_pipe)
				{
					g_a.stpsignal_inparent = 1;
					if (wait(&status) == last_childpid)
						ft_export_status(WEXITSTATUS(status), &env, &l_gc, lst);
					g_a.stpsignal_inparent = 0;
					g_a.exitstatus_singnal = 0;
					i++;
				}
				if (childpid == -1)
					ft_export_status(1, &env, &l_gc, lst);
				ft_export_anything("_=", &l_gc, lst, &env);
			}
			free(*line);
			*line = NULL;
			ft_free(&l_gc);
			cmd = NULL;
			env_lst = NULL;
		}
	}
}

void	f(void)
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	struct termios	term, term_orig;
	t_gc			*lst;
	char			*line;

	tcgetattr(STDIN_FILENO, &term);
	term_orig = term;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	// atexit(f);
	// rl_variable_bind("enable-bracketed-paste", "off");
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
