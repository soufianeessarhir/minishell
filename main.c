/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/31 05:18:05 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int parsing_part(char **line, t_env **env_lst, t_gc **l_gc, t_cmd **cmd) 
{
	t_token *token_lst;
	char **token;

	token_lst = NULL;
	token = NULL;
	if (sp_uq_handling(*line))
	  return 1;
	token = ft_tokinize(*line, l_gc);
	if (syntax_error(token, &token_lst, l_gc))
		return 1;
	her_doc_handling(&token_lst, l_gc);
	if (env_handling(&token_lst, *env_lst, l_gc))
		return 1;
	if (init_cmd(cmd, token_lst, l_gc))
		return 1;
	if (open_redirection(cmd, l_gc))
		return 1;
	return 0;
}
void readline_loop(char **line, t_gc **lst, char **env) 
{
    t_token *token_lst;
    char **token;
    t_env *env_lst;
    t_gc *l_gc;
    t_cmd *cmd;
	char **shelvl;
	char **exitstatus;
	char **tmp_env;
	int stexit;
	int flag_pipe;
	int bol;
    
    l_gc = NULL;
	stexit = -9999;
    token_lst = NULL;
    env_lst = NULL;
    cmd = NULL;
    token = NULL;
	exitstatus = NULL;
	tmp_env = NULL;

	shelvl = NULL;
	bol = 0;
	if (*env == NULL)
	{
		*env = ft_malloc(sizeof(char *) * 2, lst);
		env[0] = NULL;
		export_pwd(&env, &l_gc, lst);
	
		ft_export_anything("SHLVL=1", &l_gc, lst, &env);
		ft_export_anything("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin", &l_gc, lst, &env);
		ft_export_anything("_=/Users/relamine/Desktop/minishell/./minishell", &l_gc, lst, &env);
		bol = 1;
	}

	tmp_env = env;
	int g = 0;
	while (tmp_env != NULL && tmp_env[g])
	{
		if(ft_strcmp(tmp_env[g], "exitstatus") != 0 && tmp_env[g + 1] == NULL)
			export_status(0, &env, &l_gc, lst);
		g++;
	}
    // printf("--argv[i]: %d\n", *line);
    while (1) {
		flag_pipe = 0;
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(g_a.exitstatus_singnal);
        }
		if (g_a.exitstatus_singnal == 1)
		{
			export_status(g_a.exitstatus_singnal, &env, &l_gc, lst);
			g_a.exitstatus_singnal = 0;
		}
    	intit_env_list(&env_lst, env, lst);
        if (*line[0] != '\0')
		{	
			add_history(*line);
			if (parsing_part(line, &env_lst, &l_gc, &cmd))
			{
				free(*line);
				*line = NULL;
				ft_free(&l_gc);
				cmd = NULL;
				token_lst = NULL;
				env_lst = NULL;
				token = NULL;
				continue;
			}
	
				

			t_cmd *tmp = cmd;
			while (tmp)
			{
				tmp->flag_pipe = &flag_pipe;
				tmp->flag_display_env = &bol;
				if (tmp->next)
					flag_pipe = 1;
				stexit = ft_builtin_func(tmp, &env, &l_gc,lst);
				export_status(stexit, &env, &l_gc, lst);
				tmp = tmp->next;
			}

			free(*line);
			*line = NULL;
			ft_free(&l_gc);
			cmd = NULL;
			token_lst = NULL;
			env_lst = NULL;
			token = NULL;
		}
    }
}

void f() {
    system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
    t_gc *lst;
    char *line;
	// atexit(f);
	lst = NULL;
    if (ac != 1)
        return (printf("Usage: %s\n", av[0]),1);
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, handle_sigint);
    readline_loop(&line, &lst, env);
    ft_free(&lst);
    return 0;
}

