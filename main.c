/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/21 23:20:36 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"
void open_redirection(t_cmd **cmd , t_gc **l_gc)
{
    t_cmd *tmp;
    char **args;
    int i;

    tmp = *cmd;
    while (tmp)
    {
        if (tmp->red_in && tmp->red_in[0] != '\0')
        {
            args = ft_split(tmp->red_in, ' ', l_gc);
            i = 0;
            if (args[0] != NULL)
			{
	            while (args[i])
	            {
	                if (ft_strcmp(args[i], "<<") == 0 || ft_strcmp(args[i], "<") == 0)
	                {
	                    if (access(args[i + 1], F_OK) == -1)
	                        return(printf("minishell: %s: No such file or directory\n", args[i + 1]),(void)0);
	                    if (access(args[i + 1], R_OK) == -1)
	                        return(printf("minishell: %s: Permission denied\n", args[i + 1]),(void)0);
	                    tmp->red_in_fd = open(args[i + 1], O_RDONLY);
	                    if (tmp->red_in_fd == -1)
	                        return;
	                    i+=2;
	                }
	            }
			}
        }
		i = 0;
        if (tmp->red_out && tmp->red_out[0] != '\0')
        {
            args = ft_split(tmp->red_out, ' ', l_gc);
            if (args[0] == NULL)
			{
	            while (args[i])
	            {
	                if (ft_strcmp(args[i], ">>") == 0)
	                {
	                    tmp->red_out_fd = open(args[i + 1], O_APPEND | O_CREAT | O_RDWR, 0644);
	                    if (tmp->red_out_fd == -1)
	                        return;
	                }
	                if (ft_strcmp(args[i], ">") == 0)
	                {
	                    puts(args[i + 1]);
	                    tmp->red_out_fd = open(args[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	                    if (tmp->red_out_fd == -1)
	                        return;
	                }
	                i+=2;
	            }
			}
        }
        tmp = tmp->next;
    }
}
void readline_loop(char **line, t_gc **lst, char **env) 
{
    t_token *token_lst;
    char **token;
    t_env *env_lst;
    t_gc *l_gc;
    t_cmd *cmd;
	char **shelvl;
    
    l_gc = NULL;
    token_lst = NULL;
    env_lst = NULL;
    cmd = NULL;
    token = NULL;

	if (*env == NULL)
	{
		*env = ft_malloc(sizeof(char *) * 2, lst);
		env[0] = NULL;
		export_pwd(&env, &l_gc, lst);
		shelvl = ft_malloc(sizeof(char *) * 3, lst);
		shelvl[0] = ft_strdup("export", &l_gc);
		shelvl[1] = ft_strdup("SHLVL=1", &l_gc);
		shelvl[2] = NULL;
		ft_export(shelvl, &env,  &l_gc, lst);
	}
    
    while (1) {
    	intit_env_list(&env_lst, env, lst);
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(0);
        }
        if (*line[0] != '\0')
		{
			add_history(*line);
			
			sp_uq_handling(*line);
			token = ft_tokinize(*line, &l_gc);
			syntax_error(token, &token_lst, &l_gc);
			env_handling(&token_lst, env_lst, &l_gc);
			her_doc_handling(&token_lst, &l_gc);
			init_cmd(&cmd, token_lst, &l_gc);
			open_redirection(&cmd, &l_gc);
			for (t_cmd *tmp = cmd; tmp; tmp = tmp->next) 
			{
				printf("cmd: %s\n", tmp->cmd);
				printf("red_in: %s\n", tmp->red_in);
				printf("red_out: %s\n", tmp->red_out);
				for (int i = 0; tmp->args[i]; i++) 
				{
					printf("args[%d]: %s\n", i, tmp->args[i]);
				}
			}
			if (cmd)
			ft_builtin_func(cmd->args, &env, &l_gc,lst);
		}
	    free(*line);
	    *line = NULL;
	    ft_free(&l_gc);
	    cmd = NULL;
	    token_lst = NULL;
	    token = NULL;
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

