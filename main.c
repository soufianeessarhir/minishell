/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/05 02:06:24 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *is_env(char *str, char **env) 
{
    int i;
    int len;
    
    i = 0;
    len = strlen(str);

    while (env[i]) 
    {
        if (strncmp(str, env[i], len) == 0 && env[i][len] == '=') 
        {
            return (env[i] + len + 1);
        }
        i++;
    }
    return NULL;
}

int is_dollar(char *str) 
{
    while (*str) 
    {
        if (*str == '$') 
        {
            return 1;
        }
        str++;
    }
    return 0;
}

char *env_search(char *str, char **env) 
{
    char *result;
    int i;
    int j;
    
    i = 0;
    result = NULL;
    while (str[i]) 
    {
        if (str[i] == '$') 
        {
            j = i + 1;
            while (ft_isalnum(str[j]) || str[j] == '_') 
                j++;
            if (str[j++]=='?')
                result = ft_strjoin(result, "0");
            else if (is_env( ft_substr(str, i + 1, j - i - 1), env)) 
                result = ft_strjoin(result, is_env(ft_substr(str, i + 1, j - i - 1), env));
            i = j;
        } 
        else 
        {
            j = i;
            while (str[i] && str[i] != '$')
                i++;
            result = ft_strjoin(result, ft_substr(str, j, i - j));
        }
    }
    return result;
}

void env_handling(t_token **token_lst, char **env) 
{
    t_token *tmp;
    char *new_value;
    
    tmp = *token_lst;
    new_value = NULL;
    while (tmp) 
    {
        if (tmp->type == 1 && is_dollar(tmp->value))
        {
            new_value = env_search(tmp->value, env);
            free(tmp->value);
            tmp->value = new_value;
        }
        tmp = tmp->next;
    }
}

void    readline_loop(char **line, t_gc **lst,char **env)
{
    t_token *token_lst;

    token_lst = NULL;
    while (1)
    {
        *line = readline(BOLD GREEN "minishell" YELLOW "$ "RESET BOLD );
        if (!*line)
            break;
        if (*line[0] != '\0')
            add_history(*line);
        sp_uq_handling(*line);
        syntax_error(ft_tokinize(*line),&token_lst);
        env_handling(&token_lst,env);
        for (t_token *tmp = token_lst; tmp; tmp = tmp->next)
            printf("%s\n",tmp->value);
        free(*line);
        ft_dll_lstclear(&token_lst);
        (void)lst;
    }
    (void)env;  
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
    readline_loop(&line, &lst, env);
    return (0);
}