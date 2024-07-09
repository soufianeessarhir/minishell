/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/09 09:00:34 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void    readline_loop(char **line, t_gc **lst,char **env)
{
    t_token *token_lst;
	char **token;

    token_lst = NULL;
    while (1)
    {
        *line = readline(BOLD GREEN "minishell" YELLOW "$ "RESET BOLD );
        if (!*line)
        {
			write(0, "exit", 4);
			exit(0);
		}
        if (*line[0] != '\0')
            add_history(*line);
        // sp_uq_handling(*line);
		// for (int i = 0; token[i] != NULL; i++)
		// 	printf("%s\n", token[i]);
		token = ft_tokinize(*line);
        syntax_error(token, &token_lst);
        env_handling(&token_lst, env);
		ft_builtin_func(token, env);
		// if (ft_strcmp(token[0], "echo") == 0)
		
        // for (t_token *tmp = token_lst; tmp; tmp = tmp->next)
        //     printf("%s\n",tmp->value);
        free(*line);
		ft_dll_lstclear(&token_lst);
        (void)lst;
    }
}

void f() 
{
    system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
    t_gc *lst;
    char *line;
    if (ac != 1)
        return (printf("Usage: %s\n", av[0]),1);
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);

    return (0);
}
