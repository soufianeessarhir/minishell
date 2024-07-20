/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/20 13:08:50 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


t_cmd *new_cmd(t_gc **l_gc) 
{
    t_cmd *new;

    new = (t_cmd *)ft_malloc(sizeof(t_cmd), l_gc);
    new->cmd = ft_strdup("", l_gc);
	new->red_in = ft_strdup("", l_gc);
	new->red_out = ft_strdup("", l_gc);
	new->args = NULL;
	new->next = NULL;
	return new;
}

void ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new) {
    t_cmd *tmp;

    if (!new) return;
    if (!*lst) {
        *lst = new;
        return;
    }
    tmp = *lst;
    while (tmp->next) tmp = tmp->next;
    tmp->next = new;
}

void init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc) {
    t_token *tmp = token_lst;
    t_cmd *new;

    while (tmp) 
	{
        new = new_cmd(l_gc);
        if (!new) 
		{
            printf("Failed to create new command\n");
            return;
        }
        while (tmp && tmp->type != 3)
		{
            if (tmp->type == 2) 
			{ 
	            if (ft_strcmp(tmp->value, ">") == 0 || ft_strcmp(tmp->value, ">>") == 0) 
				{
					new->red_out = ft_strjoin(new->red_out, tmp->value, l_gc);
					new->red_out = ft_strjoin(new->red_out, " ", l_gc);
					if (tmp->next && tmp->next->type == 1) 
					{
						new->red_out = ft_strjoin(new->red_out, tmp->next->value, l_gc);
						new->red_out = ft_strjoin(new->red_out, " ", l_gc);
						tmp = tmp->next;
					}
				} 
				else if (ft_strcmp(tmp->value, "<") == 0 || ft_strcmp(tmp->value, "<<") == 0) 
				{
					new->red_in = ft_strjoin(new->red_in, tmp->value, l_gc);
					new->red_in = ft_strjoin(new->red_in, " ", l_gc);
					if (tmp->next && tmp->next->type == 1) 
					{
						new->red_in = ft_strjoin(new->red_in, tmp->next->value, l_gc);
						new->red_in = ft_strjoin(new->red_in, " ", l_gc);
						tmp = tmp->next;
					}
				}
            }
			else 
			{
                new->cmd = ft_strjoin(new->cmd, tmp->value, l_gc);
                new->cmd = ft_strjoin(new->cmd, " ", l_gc);
            }
            tmp = tmp->next;
        }
		new->args = ft_split(new->cmd, ' ', l_gc);
        ft_lstadd_back_cmd(cmd, new);
        if (tmp)
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
    
    intit_env_list(&env_lst, env, lst);
    while (1) {
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
			init_cmd(&cmd, token_lst, &l_gc);
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
			// ft_builtin_func(cmd->args, &env, &l_gc,lst);
		
			free(*line);
			*line = NULL;
			ft_free(&l_gc);
			cmd = NULL;
			token_lst = NULL;
			token = NULL;
		}
    }
   
    free(*line);
    *line = NULL;
    ft_free(&l_gc);
    cmd = NULL;
    token_lst = NULL;
    token = NULL;
}


// void f() {
//     system("leaks minishell");
// }

int	main(int ac, char **av, char **env)
{
    t_gc *lst;
    char *line;
	// atexit(f);
    if (ac != 1)
        return (printf("Usage: %s\n", av[0]),1);
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);
    ft_free(&lst);
    return 0;
}

