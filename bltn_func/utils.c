/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:57:12 by relamine          #+#    #+#             */
/*   Updated: 2024/07/25 04:35:15 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


long ft_atoi_checker(char *str)
{
	int		signe;
	long	res;

	signe = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
	{
		str++;
		if (*str == '\0')
			return(-1);
	}
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			signe = -1;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		if (res > 922337203685477580 || (res == 922337203685477580 && *str > '7' && signe == 1) ||
			(res == 922337203685477580 && *str > '8' && signe == -1))
			return (-2);
		res = res * 10 + (*(str++) - '0');
	}
	return (res * signe);
}


int ft_strlen_double(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;

	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void export_pwd(char ***envp, t_gc **l_gc, t_gc **lst)
{
    char **args = ft_malloc(sizeof(char *) * 3, l_gc);

    args[0] = ft_strdup("export ", l_gc);
    args[1] = ft_strjoin("PWD=", getcwd(NULL, 0), l_gc);
    args[2] = NULL;
    ft_export(args, envp, l_gc, lst, 0);
}

void export_oldpwd(char ***envp, t_gc **l_gc, t_gc **lst)
{
	char **args = ft_malloc(sizeof(char *) * 3, l_gc);

	args[0] = ft_strdup("export ", l_gc);
	args[1] = ft_strjoin("OLDPWD=", getcwd(NULL, 0), l_gc);
	args[2] = NULL;
	ft_export(args, envp, l_gc, lst, 0);
}

void export_status (int status, char ***envp, t_gc **l_gc, t_gc **lst)
{
	char *tmp;
	char **exitstatus;

	tmp = ft_strjoin("exitstatus=", ft_itoa(status, l_gc) ,l_gc);
	exitstatus = ft_malloc(sizeof(char *) * 3, l_gc);
	exitstatus[0] = ft_strdup("export", l_gc);
	exitstatus[1] = tmp;
	exitstatus[2] = NULL;
	ft_export(exitstatus, envp, l_gc, lst, 0);
}


void ft_export_(char **argv, char ***envpv, void *gc, void *lst)
{
    int q;
    char **tmp;
	char *arg;

    q = ft_strlen_double(argv) - 1;
    tmp = (char **)ft_malloc(sizeof(char *) * 3, lst);
    tmp[0] = ft_strdup("export", gc);
    arg = ft_strdup(argv[q], gc);
    tmp[1] = ft_strjoin("_=", arg, gc);
    tmp[2] = NULL;
    ft_export(tmp, envpv, gc, lst, 0);
}

void export_shelvl(char ***envp, t_gc **l_gc, t_gc **lst, t_env *env_lst)
{
	char *tmp;
	char **shelvl;
	char *num_shlvl;
	int i;

	num_shlvl = my_getenv("SHLVL", env_lst);
	i = ft_atoi(num_shlvl);
	if (i == 0 || i >= 10240)
		i = 1;
	else if (i < 0)
		i = 0;
	else
		i++;
	tmp = ft_strjoin("SHLVL=", ft_itoa(i, l_gc) ,l_gc);
	shelvl = ft_malloc(sizeof(char *) * 3, l_gc);
	shelvl[0] = ft_strdup("export", l_gc);
	shelvl[1] = tmp;
	shelvl[2] = NULL;
	ft_export(shelvl, envp, l_gc, lst, 0);
}

void ft_export_anything(char *argv, t_gc **l_gc, t_gc **lst, char ***env)
{
	char **tmp;

	tmp = ft_malloc(sizeof(char *) * 3, lst);
	tmp[0] = ft_strdup("export", l_gc);
	tmp[1] = ft_strdup(argv, l_gc);
	tmp[2] = NULL;
	ft_export(tmp, env, l_gc, lst, 0);
}