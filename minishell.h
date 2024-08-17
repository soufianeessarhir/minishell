/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:23:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/08/17 10:47:51 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sanitizer/lsan_interface.h>
# include <sys/stat.h>
# include <termios.h>
# include "./gc/gc.h"

typedef struct s_signalhandler
{
	int	exitstatus_singnal;
	int	stpsignal_inparent;
	int	stphedorc_insgin;
}	t_signalhandler;

t_signalhandler	g_a;

# define RESET "\033[0m"
# define GOLD "\033[0;33m"
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"
//background colors
# define BGBLACK "\033[40m"
# define BGRED "\033[41m"
# define BGGREEN "\033[42m"
# define BGYELLOW "\033[43m"
# define BGBLUE "\033[44m"
# define BGMAGENTA "\033[45m"
# define BGCYAN "\033[46m"
# define BGWHITE "\033[47m"
# define BOLDMAGENTA "\033[1;35m"
# define RESET "\033[0m"
# define BOLDYELLOW "\033[1;33m"
# define BOLDGREEN "\033[1;32m"

typedef struct s_help
{
	char	*line;
	char	***env;
	t_gc	**lst;
}	t_help;

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
	int				is_env;
}	t_token;

typedef struct s_env_vars
{
	int					i;
	int					j;
	char				*src;
	char				*value;
	char				*result;
	char				quote;
	struct s_env_vars	*next;
}	t_env_vars;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	char			*redio;
	struct s_redir	*next;
}	t_redir;

typedef struct s_srgs
{
	char			*arg;
	struct s_srgs	*next;
}	t_args;

typedef struct s_cmd
{
	t_args			*args_lst;
	char			**args;
	t_redir			*rd;
	int				red_in_fd;
	int				red_out_fd;
	int				exit_status;

	int				*flag_pipe;
	int				*flag_display_env;
	int				num_cmd;
	char			*path_of_program;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env_h
{
	int		i;
	char	*result;
	char	*tmp;
	t_env	*env_lst;
	t_gc	**l_gc;
	char	*str;
}	t_env_h;
typedef struct s_heredoc
{
	char	*line;
	int		fd;
	char	*delimiter;

}	t_heredoc;

t_token		*ft_dll_lstnew(char *content, int type, t_gc **l_gc);
void		ft_dll_lstadd_front(t_token **lst, t_token *new);
void		ft_dll_lstadd_back(t_token **lst, t_token *new);
void		ft_dll_lstclear(t_token **lst);
t_token		*ft_dll_lstlast(t_token *lst);
int			ft_dll_lstsize(t_token *lst);
void		ft_tokinize(char *line, t_token **token_lst, t_gc **l_gc);
void		init_graph(int graph[4][3]);
int			syntax_error(t_token **token, t_gc **l_gc, t_env *env_lst);
int			sp_uq_handling(char *line);
int			init_cmd(t_cmd **cmd, t_token *token_lst, t_gc **l_gc);
void		her_doc_handling(t_token **token_lst, t_gc **l_gc, t_env *env_lst);
t_env		*new_env(char *key, char *value, t_gc **lst);
void		env_add_back(t_env **env_lst, t_env *new);
void		intit_env_list(t_env **env_lst, char **env, t_gc **lst);
char		*my_getenv(char *key, t_env *env_lst);
char		*env_search(char *str, t_env *env_lst, t_gc **l_gc, int numcmd);
void		env_handling(t_token **token_lst, t_env *env_lst, t_gc **l_gc);
int			open_redirection(t_cmd **cmd, t_gc **l_gc);
char		*clean_str(char *str, t_gc **l_gc);
int			is_dollar(char *str);
t_redir		*new_redir(char *red_in, t_gc **l_gc);
t_args		*new_args(char *arg, t_gc **l_gc);
void		ft_lstadd_back_args(t_args **lst, t_args *new);
t_cmd		*new_cmd(t_gc **l_gc);
char		**ft_fill_args(t_args *args_lst, t_gc **l_gc);
int			sp_in_it(char *str);
int			is_all_dollar(char *str);
char		*expand_double_dollar(char *str, t_gc **l_gc);
t_env_vars	*new_env_vars(char *value, t_gc **l_gc);
void		env_lstadd_back(t_env_vars **alst, t_env_vars *new);
int			is_dollar(char *str);
char		*env_search(char *str, t_env *env_lst, t_gc **l_gc, int numcmd);
char		*helper(char *s, t_gc **l_gc, t_env *env_lst, int numcmd);
int			handle_red_in(t_cmd *tmp, t_gc **l_gc, t_redir *rd);
int			handle_append_redirection(t_cmd *tmp, char *redout, t_gc **l_gc);
int			handle_overwrite_redirection(t_cmd *tmp, char *redout, t_gc **l_gc);
int			handle_red_out(t_cmd *tmp, t_gc **l_gc, t_redir *rd);
int			handle_redirections(t_cmd *tmp, t_gc **l_gc);
int			is_path(char *str);
char		*handle_exit_status(char *result,
				t_env *env_lst, t_gc **l_gc, int numcmd);
char		*handle_env_variable(char *str, int *i, char *result, t_env_h *tmp);
char		*handle_non_variable(char *str, int *i, char *result, t_gc **l_gc);
char	*trim_dir(char	*str,t_gc **l_gc);
char 		*expand_sl(char *str, t_gc **l_gc);



void		handle_sigint(int sig);
int			echo(int argc, char **argv);
int			ft_builtin_func(t_cmd *cmd, char ***env, t_gc **l_gc, t_gc **lst);
int			pwd(void);
int			exit_0(int i, int argc, char **argv, int *flag_pipe);
int			env(char **env, t_gc **lst, int bol);
int			ft_strlen_double(char **str);
int			cd(char **argv, char ***envp, t_gc **gc, t_gc **lst);
int			ft_execute(t_cmd *cmd, char ***envp, t_gc **l_gc, t_gc **lst);
int			ft_export(char **argv, char ***envp, t_gc **gc,
				t_gc **lst, int *boll);
int			ft_strcmp(const char *s1, const char *s2);
void		export_pwd(char *which, char ***envp, t_gc **l_gc, t_gc **lst);
char		*get_value(char *str, t_gc **l_gc);
char		*get_key(char *str, t_gc **l_gc);
int			unset(char **argv, char ***env_lst, t_gc **gc, t_gc **lst);
void		ft_export_status(int status, char ***envp, t_gc **l_gc, t_gc **lst);
void		ft_export_(char **argv, char ***envpv, t_gc **gc, t_gc **lst);
void		export_shelvl(char ***envp, t_gc **l_gc,
				t_gc **lst, t_env *env_lst);
void		ft_export_anything(char *argv, t_gc **l_gc,
				t_gc **lst, char ***env);
int			ft_isonlydigit(char *str);
void		system_export_config(char *key, char *value, char ***envp, t_gc **lst);
int			setup_env_and_path(char ***env, t_gc **lst, t_gc **l_gc);
void		check_and_export_status(char ***env, t_gc **l_gc, t_gc **lst);
void		print_exported_variables(char **envp, t_gc **gc, int bol);



#endif
