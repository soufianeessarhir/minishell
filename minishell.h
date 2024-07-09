/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:23:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/09 11:17:41 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
#include <signal.h>
#include <sys/types.h>

#include "./gc/gc.h"


#define RESET "\033[0m"
#define GOLD "\033[0;33m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
//background colors
#define BGBLACK "\033[40m"
#define BGRED "\033[41m"
#define BGGREEN "\033[42m"
#define BGYELLOW "\033[43m"
#define BGBLUE "\033[44m"
#define BGMAGENTA "\033[45m"
#define BGCYAN "\033[46m"
#define BGWHITE "\033[47m"

typedef struct s_token
{
    char *value;
    int type;
    struct s_token *next;
    struct s_token *prev;
}               t_token;

typedef struct s_env_vars
{
    int i;
    int j;
    char *src;
    char *value;
    char *result;
    int is_expandable;
}               t_env_vars;
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}               t_env;

t_token *ft_dll_lstnew(char *content, int type);
void    ft_dll_lstadd_front(t_token **lst, t_token *new);
void    ft_dll_lstadd_back(t_token **lst, t_token *new);
void    ft_dll_lstclear(t_token **lst);
t_token *ft_dll_lstlast(t_token *lst);
int     ft_dll_lstsize(t_token *lst);
char    **ft_tokinize(char *line);
void    help(char *line,char **sep_token,int *j,int *i);
void    skip_quoted(char **sep_token,char *line, int *i,int *j);
void  init_graph(int graph[4][3]);
int syntax_error(char **args,t_token **token);
int sp_uq_handling (char *line);


t_env *new_env(char *key, char *value);
void env_add_back(t_env **env_lst, t_env *new);
void  intit_env_list(t_env **env_lst, char **env);
char *my_getenv(char *key, t_env *env_lst);
int is_expandabe(char *str, int i, int j);
int check_ex(char *str,int end);
char *env_search(char *str,char **env);
void env_handling(t_token **token_lst, char **env);


void handle_sigint(int sig);
int echo(int argc, char **argv);
void ft_builtin_func(char **token, char **env);
int pwd(void);
void exit_0(int j);
int env(char **env);
int ft_strlen_double(char **str);
long ft_atoi_checker(char *str);
void unset(const char *argv, char **env);



#endif