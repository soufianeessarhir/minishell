/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/07 16:11:37 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_ex(char *str) 
{
    int i;
    int j;
    int flag;
    char quote;
    
    i = 0;
    j = 0;
    flag = 0;
    while (str[i])
    {
        if ( str[i] == '\"')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote)
               i++;
            i++;
        }
        else if (str[i] == '\'')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote)
                i++;
            if (str[i] != quote)
                flag = 1;
            i++;
        }
    }
    return flag;
}

int is_dollar(char *str) 
{
    while (*str) 
    {
        if (*str == '$') 
            return 1;
        str++;
    }
    return 0;
}

char *cleand_str(char *str) 
{
    int i;
    int j;
    char quote;
    
    i = 0;
    j = 0;
    
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '\"')
        {
            quote = str[i++];
            while (str[i] && str[i] != quote)
                str[j++] = str[i++];
            i++;
        }
        else
            str[j++] = str[i++];
    }
    str[j] = '\0';
    return str;
}
int is_expandabe(char *str,int start,int end) 
{
    char *tmp;
    char *tmp3;

    while (str[start] == str[end] && (str[start] == '\'' || str[start] == '\"'))
    {
        start--;
        end++;
    }
    start++;
    while (str[start] == str[start + 1])
    { 
        start= start + 2;
        end = end - 2;
    }
    tmp = ft_substr(str, start, end - start);
    tmp3 = ft_strdup(tmp);
    end = 0;
    while (tmp[end] != '$' && tmp[end] != '\0')
        end++;
    if(check_ex(ft_substr(tmp3, 0, end)))
        return 0;
    return 1;
}

char *env_search(char *str) 
{
    t_env *tmp;

    tmp = malloc(sizeof(t_env));
    tmp->i = 0;
    tmp->j = 0;
    tmp->result = NULL;
    while (str[tmp->i]) 
    {
        if (str[tmp->i] == '$')
        {
            if (str[tmp->i + 1] == '?')
            {
                tmp->result = ft_strjoin(tmp->result, ft_itoa(errno));
                tmp->i += 2;
                continue;
            }
            tmp->j = tmp->i;
            tmp->i++;
            while ((ft_isalnum(str[tmp->i]) || str[tmp->i] == '_') && str[tmp->i])
                tmp->i++;
            if (is_expandabe(str,tmp->j - 1,tmp->i))
                tmp->result = ft_strjoin(tmp->result,getenv(ft_substr(str, tmp->j + 1, tmp->i - tmp->j - 1)));
            else
                tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j));
            tmp->j = tmp->i;
        }
        else
        {
            tmp->j = tmp->i;
            while (str[tmp->i] != '$' && str[tmp->i])
                tmp->i++;
            tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i - tmp->j));
        }
    }
    return cleand_str(tmp->result);  
}

void env_handling(t_token **token_lst) 
{
    t_token *tmp;
    char *new_value;
    tmp = *token_lst;
    new_value = NULL;
    while (tmp) 
    {
        if (tmp->type == 1 && is_dollar(tmp->value))
        {
            new_value = env_search(tmp->value);
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
        env_handling(&token_lst);
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
