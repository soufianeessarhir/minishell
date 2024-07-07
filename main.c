/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/07 08:46:22 by relamine         ###   ########.fr       */
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
// char *grep_env(char *str) 
// {
//     int i;
//     int j;
//     char *value;
    
//     i = 0;
//     j = 0;
//     while (str[i] && str[i] != '$')
//         i++;
//     j = i++;
//     if (str[i] == '?')
//         return ft_strdup("0");
//     while ((ft_isalnum(str[i]) || str[i] == '_') && str[i])
//         i++;
//     value = ft_substr(str, j, i - j);
//     return value;
// }
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
    char *tmp2;
    char *tmp3;
    
    while (str[start] == str[end] && (str[start] == '\'' || str[start] == '\"'))
    {
        start--;
        end++;
    }
    start++;
    tmp = ft_substr(str, start, end - start);
    tmp3 = ft_strdup(tmp);
    tmp2 = cleand_str(tmp3);
    if ((tmp[0] == '\'' && tmp2[0] == '\'') || (tmp[0] == '\'' && (tmp[1] != '\'' && tmp2[1] != '\"')))
        return 0;
    return 1;
}

char *env_search(char *str, char **env) 
{
    t_env *tmp;

    tmp = malloc(sizeof(t_env));
    tmp->i = -1;
    tmp->j = 0;
    tmp->result = NULL;
    while (str[++tmp->i]) 
    {
        while (str[tmp->i] && str[tmp->i] != '$')
            tmp->i++;
        tmp->result = ft_strjoin(tmp->result, ft_substr(str, tmp->j, tmp->i));
        if (str[tmp->i] == '$' && str[tmp->i + 1] == '?')
        {
            tmp->result = ft_strjoin(tmp->result,ft_strdup("0"));
            tmp->i++;
        } 
        else
        {
            tmp->j = tmp->i;
            tmp->i++;
            while ((ft_isalnum(str[tmp->i]) || str[tmp->i] == '_') && str[tmp->i])
                tmp->i++;
            if (is_expandabe(str,tmp->j - 1,tmp->i))
            {
                tmp->src = ft_substr(str, tmp->j + 1, tmp->i - tmp->j- 1);
                tmp->value = is_env(tmp->src, env);
                if (tmp->value)
                    tmp->result = ft_strjoin(tmp->result, tmp->value);
                else
                    tmp->result = ft_strjoin(tmp->result, tmp->src);
                free(tmp->src);
            }
            else
            {
                tmp->src = ft_substr(str, tmp->j, tmp->i - tmp->j);
                tmp->result = ft_strjoin(tmp->result, tmp->src);
                free(tmp->src);
            }
        }
        tmp->j = tmp->i;
    }
    return cleand_str(tmp->result);  
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
        sp_uq_handling(*line);
		// for (int i = 0; token[i] != NULL; i++)
		// 	printf("%s\n", token[i]);
		token = ft_tokinize(*line);
        syntax_error(token, &token_lst);
		ft_builtin_func(token);
		// if (ft_strcmp(token[0], "echo") == 0)
		//
        env_handling(&token_lst,env);
        // for (t_token *tmp = token_lst; tmp; tmp = tmp->next)
        //     printf("%s\n",tmp->value);
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
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);

    return (0);
}
