/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/06/28 01:29:27 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int check_quote(char *line)
{
    int i;
    int quote;
    int dquote;

    i = 0;
    quote = 0;
    dquote = 0;
    while (line[i])
    {
        if (line[i] == '\'')
            quote++;
        if (line[i] == '\"')
            dquote++;
        i++;
    }
    if (quote % 2 != 0 || dquote % 2 != 0)
        return (1);
    return (0);
}
void    readline_loop(char **line)
{
    while (1)
    {
        *line = readline(BOLD GREEN "minishell" YELLOW "$ "RESET BOLD );
        if (!*line)
            break;
        if (*line[0] != '\0')
            add_history(*line);
        while(check_quote(*line) == 1)
        {
            *line = ft_strjoin(*line, readline(BOLD GREEN "> "RESET BOLD));
            if (!*line)
                break;
            if (*line[0] != '\0')
                add_history(*line);
        }
        printf("%s\n", *line);
        free(*line);
    }
}
int	main(int ac, char **av, char **env)
{
   
    char *line;
    readline_loop(&line);
    (void)ac;
    (void)av;
    (void)env;
    return (0);
}