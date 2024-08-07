/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:23:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/07 11:57:30 by relamine         ###   ########.fr       */
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
#include <sanitizer/lsan_interface.h>
#include <sys/stat.h>

#include "./gc/gc.h"


typedef struct g_signalhandler
{
	int exitstatus_singnal;
	int stpsignal_inparent;
	int stphedorc_insgin;
} 			 t_signalhandler;

t_signalhandler g_a;

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
#define BOLDMAGENTA "\033[1;35m"
#define RESET "\033[0m"
#define BOLDYELLOW "\033[1;33m"
#define BOLDGREEN "\033[1;32m"
typedef struct s_help
{
	char *line;
	char ***env;
	t_gc **lst;
}t_help;
typedef struct s_token
{
    char *value;
    int type;
    struct s_token *next;
    struct s_token *prev;
	int is_env;
}               t_token;

typedef struct s_env_vars
{
    int i;
    int j;
    char *src;
    char *value;
    char *result;
   char quote;
    struct s_env_vars *next;
}               t_env_vars;
typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
}               t_env;
typedef struct s_redir
{
	char *redio;
	struct s_redir *next;
}               t_redir;

typedef struct s_srgs
{
	char *arg;
	struct s_srgs *next;
}               t_args;


typedef struct s_cmd
{
    t_args *args_lst;
	char **args;
	t_redir *rd;
	int red_in_fd;
	int red_out_fd;

	int *flag_pipe;
	int *flag_display_env;
	int num_cmd;
	char *path_of_program;
    struct s_cmd *next;
	struct s_cmd *prev;
}               t_cmd;

// void print_full_art();
t_token *ft_dll_lstnew(char *content, int type, t_gc **l_gc);
void    ft_dll_lstadd_front(t_token **lst, t_token *new);
void    ft_dll_lstadd_back(t_token **lst, t_token *new);
void    ft_dll_lstclear(t_token **lst);
t_token *ft_dll_lstlast(t_token *lst);
int     ft_dll_lstsize(t_token *lst);
void ft_tokinize(char *line,t_token **token_lst,t_gc **l_gc);
void  init_graph(int graph[4][3]);
int syntax_error(t_token **token,t_gc **l_gc);
int sp_uq_handling (char *line);
int  init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc);
void her_doc_handling(t_token **token_lst, t_gc **l_gc);
t_env	*new_env(char *key, char *value, t_gc **lst);
void env_add_back(t_env **env_lst, t_env *new);
void  intit_env_list(t_env **env_lst, char **env, t_gc **lst);
char *my_getenv(char *key, t_env *env_lst);
char *env_search(char *str, t_env *env_lst, t_gc **l_gc);
int env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc);
void open_redirection(t_cmd **cmd , t_gc **l_gc,t_help *help);
char *clean_str(char *str, t_gc **l_gc); 
int is_dollar(char *str);

void handle_sigint(int sig);
int echo(int argc, char **argv, char ***envp, t_gc **lst);
int ft_builtin_func(t_cmd *cmd, char ***env, t_gc **l_gc,t_gc **lst);
int pwd(void);
void exit_0(int i, int argc, char **argv);
int env(char **env, t_gc **lst, int bol);
int ft_strlen_double(char **str);
long ft_atoi_checker(char *str, int *error_msg);
int cd(char **argv, char ***envp, t_gc **gc, t_gc **lst);
int ft_execute(t_cmd *cmd, char ***envp, t_gc **l_gc, t_gc **lst);
int ft_export(char **argv, char ***envp, t_gc **gc, t_gc **lst, int *boll);
int	ft_strcmp(const char *s1, const char *s2);
void export_pwd(char ***envp, t_gc **l_gc, t_gc **lst);
void export_oldpwd(char ***envp, t_gc **l_gc, t_gc **lst);
char *get_value(char *str, t_gc **l_gc);
char *get_key(char *str, t_gc **l_gc);
int unset(char **argv, char ***env_lst, t_gc **gc, t_gc **lst);
void export_status (int status, char ***envp, t_gc **l_gc, t_gc **lst);
void ft_export_(char **argv, char ***envpv, t_gc **gc, t_gc **lst);
void export_shelvl(char ***envp, t_gc **l_gc, t_gc **lst, t_env *env_lst);
void ft_export_anything(char *argv, t_gc **l_gc, t_gc **lst, char ***env);
int ft_isonlydigit(char *str);
void sort_env_list(t_env **env_lst);

#endif
