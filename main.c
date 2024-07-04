/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/04 17:01:51 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int  is_exist(char *str,char c,int *i)
{
    while (str[++(*i)] != '\0')
    {
        if (str[*i] == '/' || str[*i] == ';')
            return (0);
        if (str[*i] == c)
            return (1);
    }
    return (0);
}
int sp_uq_handling (char *line)
{
    int i;

    i = -1;
    while (line[++i])
    {
        if ((line[i] == ';' || line[i] == '/') || (line[i] == '\'' && !is_exist(line,'\'',&i))
            || (line[i] == '\"' && !is_exist(line,'\"',&i)))
            return (printf("syntax error \n"),1);
    }
    return (0);
}

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
        sp_uq_handling(*line);
        continue;
        token = ft_tokinize(*line);
        syntax_error(token);
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
    readline_loop(&line, &lst);
    (void)ac;
    (void)av;
    (void)env;
    return (0);
}