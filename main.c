/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/24 12:13:07 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void readline_loop(char **line, t_gc **lst, char **env) 
{
    t_token *token_lst;
    char **token;
    t_env *env_lst;
    t_gc *l_gc;
    t_cmd *cmd;
	char **shelvl;
	char **tmp;
	int bol = 0;
	char **exitstatus;
	char **tmp_env;
	int stexit;
	int flag_pipe;
    
    l_gc = NULL;
	stexit = -9999;
    token_lst = NULL;
    env_lst = NULL;
    cmd = NULL;
    token = NULL;
	exitstatus = NULL;
	tmp_env = NULL;

	shelvl = NULL;
	if (*env == NULL)
	{
		*env = ft_malloc(sizeof(char *) * 2, lst);
		env[0] = NULL;
		export_pwd(&env, &l_gc, lst);
		shelvl = ft_malloc(sizeof(char *) * 3, lst);
		shelvl[0] = ft_strdup("export", &l_gc);
		shelvl[1] = ft_strdup("SHLVL=1", &l_gc);
		shelvl[2] = NULL;
		ft_export(shelvl, &env,  &l_gc, lst, &bol);
	
		tmp = ft_malloc(sizeof(char *) * 3, lst);
		tmp[0] = ft_strdup("export", &l_gc);
		tmp[1] = ft_strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin", &l_gc);
		tmp[2] = NULL;
		ft_export(tmp, &env,  &l_gc, lst, &bol);

		tmp = ft_malloc(sizeof(char *) * 3, lst);
		tmp[0] = ft_strdup("export", &l_gc);
		tmp[1] = ft_strdup("_=/Users/relamine/Desktop/minishell/./minishell", &l_gc);
		tmp[2] = NULL;
		ft_export(tmp, &env,  &l_gc, lst, &bol);

		bol = 1;
	}

	tmp_env = env;
	int g = 0;
	while (tmp_env != NULL && tmp_env[g])
	{
		if(ft_strcmp(tmp_env[g], "exitstatus") != 0 && tmp_env[g + 1] != NULL)
			export_status(0, &env, &l_gc, lst);
		g++;
	}
    
    while (1) {
		flag_pipe = 0;
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(0);
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
			
			// sp_uq_handling(*line);
			token = ft_tokinize(*line, &l_gc);
			syntax_error(token, &token_lst, &l_gc);
			env_handling(&token_lst, env_lst, &l_gc);
			her_doc_handling(&token_lst, &l_gc);
			init_cmd(&cmd, token_lst, &l_gc);
			open_redirection(&cmd, &l_gc);
			// for (t_cmd *tmp = cmd; tmp; tmp = tmp->next) 
			// {
			// 	printf("cmd: %s\n", tmp->cmd);
			// 	printf("red_in: %s\n", tmp->red_in);
			// 	printf("red_out: %s\n", tmp->red_out);
			// 	for (int i = 0; tmp->args[i]; i++) 
			// 	{
			// 		printf("args[%d]: %s\n", i, tmp->args[i]);
			// 	}
			// }
			while (cmd)
			{
				if (cmd->next)
					flag_pipe = 1;
				if (!flag_pipe)
					ft_export_(cmd->args, &env, &l_gc, lst);
				else
				{
					tmp = ft_malloc(sizeof(char *) * 3, lst);
					tmp[0] = ft_strdup("export", &l_gc);
					tmp[1] = ft_strdup("_=", &l_gc);
					tmp[2] = NULL;
					ft_export(tmp, &env,  &l_gc, lst, 0);
				}
				stexit = ft_builtin_func(cmd->args, &env, &l_gc,lst, &bol);
				if (stexit != -9999)
					export_status(stexit, &env, &l_gc, lst);
				cmd = cmd->next;
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
    readline_loop(&line, &lst, env);
    ft_free(&lst);
    return 0;
}

