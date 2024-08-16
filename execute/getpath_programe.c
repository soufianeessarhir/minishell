/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath_programe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:26:44 by relamine          #+#    #+#             */
/*   Updated: 2024/08/16 01:49:22 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **create_tmp_env(char *cmd1, char *cmd2, t_gc **l_gc)
{
    char **tmp;

	tmp = ft_malloc(sizeof(char *) * 3, l_gc);
    tmp[0] = ft_strdup(cmd1, l_gc);
    tmp[1] = ft_strdup(cmd2, l_gc);
    tmp[2] = NULL;
    return tmp;
}

void unset_tmp_env(char *var, char ***env, t_gc **l_gc, t_gc **lst)
{
    char **tmp;

	tmp = create_tmp_env("unset", var, l_gc);
    unset(tmp, env, l_gc, lst);
}

void setup_default_env(t_env **env_lst, char ***env, char **path_of_program, t_gc **l_gc, t_gc **lst)
{
    char **tmp;

    tmp = create_tmp_env("cd", "..", l_gc);
    cd(tmp, env, l_gc, lst);
    intit_env_list(env_lst, *env, l_gc);
    *path_of_program = ft_strjoin(my_getenv("OLDPWD", *env_lst), "/./minishell", l_gc);
    unset_tmp_env("OLDPWD", env, l_gc, lst);
    unset_tmp_env("_", env, l_gc, lst);
}

int handle_env_setup(char **path_of_program, t_env **env_lst, t_gc **l_gc, t_gc **lst, char ***env)
{
	int env_i;
	char *pwd;

	env_i = 0;
	pwd = my_getenv("PWD", *env_lst);
    if (**env == NULL)
	{
		env_i = 1;
        setup_default_env(env_lst, env, path_of_program, l_gc, lst);
		chdir(pwd);
	}
    else
        *path_of_program = ft_strjoin(pwd, "/./minishell", l_gc);
    ft_export_path_program(*path_of_program, env, lst);
	return	(env_i);
}

int setup_env_and_path(char ***env, t_gc **lst, t_gc **l_gc)
{
	char *path_of_program;
	t_env	*env_lst;

	env_lst = NULL;
	path_of_program = NULL;
    intit_env_list(&env_lst, *env, l_gc);
    if (!path_of_program && !my_getenv("@path_of_program", env_lst))
       if (handle_env_setup(&path_of_program, &env_lst, l_gc, lst, env))
	   {
			ft_export_anything("SHLVL=1", l_gc, lst, env);
			ft_export_anything("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin", l_gc, lst, env);
			ft_export_anything(ft_strjoin("_=", path_of_program, lst), l_gc, lst, env);
			return (1);
	   }
	return (0);
}
