/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/06 00:06:20 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    readline_loop(char **line, t_gc **lst)
{
    char **token;
    
    while (1)
    {
        *line = readline(BOLD GREEN "minishell" YELLOW "$ "RESET BOLD );
        if (!*line)
            break;
        if (*line[0] != '\0')
            add_history(*line);
        token = ft_tokinize(*line);
        syntax_error(token);
        // for (int i = 0; token[i] != NULL; i++)
        //     printf("%s\n", token[i]);
      
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
    int i;
    i = 0;

	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst);
    (void)ac;
    (void)av;
    (void)env;
	//handling singals
    return (0);
}