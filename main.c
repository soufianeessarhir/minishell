/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 04:24:26 by sessarhi          #+#    #+#             */
/*   Updated: 2024/07/18 00:38:19 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void her_doc_handling(t_token **token_lst)
{
    t_token *tmp;
    t_token *tmp2;
    t_token *tmp3;
    char *line;
    int i;
    int fd;

    if (!token_lst || !*token_lst)
        return;
    i = 0;
    tmp = *token_lst;
    if (!tmp->next)
        return;
    fd = open(ft_strjoin("/tmp/",tmp->next->value), O_CREAT | O_RDWR | O_TRUNC, 0644);
    while (tmp)
    {
        if (tmp->type == 2 && strncmp(tmp->value, "<<", 2) == 0)
        {
            while (1)
            {
                line = readline(">");
                if (!line || ft_strncmp(line, tmp->next->value, ft_strlen(line)) == 0)
                    break;
                write(fd, line, ft_strlen(line));
                write(fd, "\n", 1);
            }
            close(fd);
            tmp2 = tmp->prev;
            if (tmp->next)
                tmp3 = tmp->next->next;
            else
                tmp3 = NULL;
            if (tmp->value)
                free(tmp->value);
            if (tmp->next && tmp->next->value)
                free(tmp->next->value);
            if (tmp->next)
                free(tmp->next);
            free(tmp);
            if (tmp2)
                tmp2->next = tmp3;
            if (tmp3)
                tmp3->prev = tmp2;
            tmp = tmp3;
        }
        if (tmp)
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
			write(0, "exit\n", 5);
			exit(0);
		}
        if (*line[0] != '\0')
            add_history(*line);
        // sp_uq_handling(*line);
		// for (int i = 0; token[i] != NULL; i++)
		// 	printf("%s\n", token[i]);
		token = ft_tokinize(*line);
        syntax_error(token, &token_lst);
        her_doc_handling(&token_lst);
        env_handling(&token_lst, env);

		// if (ft_strcmp(token[0], "echo") == 0)
		//
		
		// change list to double pointer
		int i = ft_strlen_double(token);
		char **list = malloc((i + 1) * sizeof(char *));
		while (i >= 0)
		{
			list[i] = NULL;
			i--;
		}
		int d = 0;
        for (t_token *tmp = token_lst; tmp; tmp = tmp->next)
		{
			list[d] = ft_strjoin(list[d], tmp->value);
			d++;
		}
		ft_builtin_func(list, &env);
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
	char **shelvl;

    if (ac != 1)
        return (printf("Usage: %s\n", av[0]),1);
	if (*env == NULL)
	{
		*env = malloc(sizeof(char *) * 2);
		env[0] = NULL;
		export_pwd(&env);
		shelvl = malloc(sizeof(char *) * 3);
		shelvl[0] = ft_strdup("export");
		shelvl[1] = ft_strdup("SHLVL=1");
		shelvl[2] = NULL;
		ft_export(shelvl,&env);
	}
	rl_catch_signals = 0;
    signal(SIGINT, handle_sigint);
    readline_loop(&line, &lst, env);

    return (0);
}
