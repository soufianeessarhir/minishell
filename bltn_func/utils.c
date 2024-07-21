/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:57:12 by relamine          #+#    #+#             */
/*   Updated: 2024/07/21 11:09:10 by relamine         ###   ########.fr       */
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
