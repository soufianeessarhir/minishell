/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/15 05:08:15 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"


t_cmd *new_cmd(char *cmd, char *redir, t_gc **l_gc) {
    t_cmd *new;

    new = (t_cmd *)ft_malloc(sizeof(t_cmd), l_gc);
    if (!new) return NULL;
    new->cmd = cmd ? cmd : ft_strdup("", l_gc);
    new->redirection = redir ? redir : ft_strdup("", l_gc);
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

    while (tmp) {
        new = new_cmd(NULL, NULL, l_gc);
        if (!new) {
            printf("Failed to create new command\n");
            return;
        }
        while (tmp && tmp->type != 3) { // Assuming type 3 indicates a command separator
            if (tmp->type == 2) { // Assuming type 2 indicates a redirection token
                new->redirection = ft_strjoin(new->redirection, tmp->value, l_gc);
                new->redirection = ft_strjoin(new->redirection, " ", l_gc);
                if (tmp->next) {
                    new->redirection = ft_strjoin(new->redirection, tmp->next->value, l_gc);
                    new->redirection = ft_strjoin(new->redirection, " ", l_gc);
                    tmp = tmp->next;
                }
            } else {
                new->cmd = ft_strjoin(new->cmd, tmp->value, l_gc);
                new->cmd = ft_strjoin(new->cmd, " ", l_gc);
            }
            tmp = tmp->next;
        }
        ft_lstadd_back_cmd(cmd, new);
        if (tmp) tmp = tmp->next;
    }
}

void readline_loop(char **line, t_gc **lst, char **env) {
    t_token *token_lst;
    char **token;
    t_env *env_lst;
    t_gc *l_gc;
    t_cmd *cmd;
    
    l_gc = NULL;
    token_lst = NULL;
    env_lst = NULL;
    cmd = NULL;
    token = NULL;
    
    intit_env_list(&env_lst, env, lst);
    while (1) {
        *line = readline(BOLD GREEN "minishell" YELLOW "$ " RESET BOLD);
        if (!*line) {
            write(0, "exit\n", 5);
            exit(0);
        }
        if (*line[0] != '\0') add_history(*line);
        
        // sp_uq_handling(*line);
        token = ft_tokinize(*line, &l_gc);
        syntax_error(token, &token_lst, &l_gc);
        env_handling(&token_lst, env_lst, &l_gc);
        init_cmd(&cmd, token_lst, &l_gc);
		for (t_token *tmp = token_lst; tmp; tmp = tmp->next) 
			printf("value: %s\n", tmp->value);
        // ft_builtin_func(cmd, env, &l_gc);
       
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

int main(int ac, char **av, char **env) {
    t_gc *lst = NULL;
    char *line = NULL;

    atexit(f);
    if (ac != 1) return (printf("Usage: %s\n", av[0]), 1);
    rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);
    ft_free(&lst);
    return 0;
}

