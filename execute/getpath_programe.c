/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpath_programe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 00:26:44 by relamine          #+#    #+#             */
/*   Updated: 2024/08/18 17:26:23 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **create_tmp_env(char *cmd1, char *cmd2, t_gc **l_gc)
{
    char **tmp;

	tmp = ft_malloc(sizeof(char *) * 3, l_gc);
    tmp[0] = ft_strdup(cmd1, l_gc);
    tmp[1] = ft_strdup(cmd2, l_gc);
    tmp[2] = NULL;
    return tmp;
}

static void unset_tmp_env(char *var, char ***env, t_gc **l_gc, t_gc **lst)
{
    char **tmp;

	tmp = create_tmp_env("unset", var, l_gc);
    unset(tmp, env, l_gc, lst);
}

static char  *setup_default_env(t_env **env_lst, char ***env, char **path_of_program, t_norm free_list)
{
    char **tmp;
	char *pwd_env_i;

    tmp = create_tmp_env("cd", "..", free_list.l_gc);
    cd(tmp, env, free_list.l_gc, free_list.lst);
    intit_env_list(env_lst, *env, free_list.l_gc);
    *path_of_program = ft_strjoin(my_getenv("OLDPWD", *env_lst), "/./minishell", free_list.l_gc);
	pwd_env_i = my_getenv("OLDPWD", *env_lst);
    unset_tmp_env("OLDPWD", env, free_list.l_gc, free_list.lst);
    unset_tmp_env("_", env, free_list.l_gc, free_list.lst);
	return (pwd_env_i);
}

static int handle_env_setup(char **path_of_program, t_env **env_lst, t_norm free_list, char ***env)
{
	int env_i;
	char *pwd;
	char *tmp_pwd;

	env_i = 0;
	pwd = my_getenv("PWD", *env_lst);
    if (**env == NULL)
	{
		env_i = 1;
        tmp_pwd = setup_default_env(env_lst, env, path_of_program,  free_list);
		ft_export_anything(ft_strjoin("PWD=", tmp_pwd, free_list.lst),  free_list.l_gc, free_list.lst, env);
		chdir(tmp_pwd);
	}
    else
        *path_of_program = ft_strjoin(pwd, "/./minishell",  free_list.l_gc);
	ft_export_anything("OLDPWD",  free_list.l_gc, free_list.lst, env);
    system_export_config("@path_of_program=", *path_of_program, env, free_list.lst);
	return	(env_i);
}

int setup_env_and_path(char ***env, t_gc **lst, t_gc **l_gc)
{
	char *path_of_program;
	t_env	*env_lst;
	int		env_i;
	t_norm	free_list;

	env_lst = NULL;
	path_of_program = NULL;
    intit_env_list(&env_lst, *env, l_gc);
	env_i = 0;
	free_list.l_gc = l_gc;
	free_list.lst = lst;
	if (my_getenv("@hidden_PATH", env_lst))
		env_i = 1;
    if (!path_of_program && !my_getenv("@path_of_program", env_lst))
	{
       if (handle_env_setup(&path_of_program, &env_lst, free_list, env))
	   {
			ft_export_anything("SHLVL=1", l_gc, lst, env);
			ft_export_anything("PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/sbin", l_gc, lst, env);
			ft_export_anything(ft_strjoin("_=", path_of_program, lst), l_gc, lst, env);
			system_export_config("@hidden_PATH=", "1", env, lst);
			return (1);
	   }
	}
	return (env_i);
}
