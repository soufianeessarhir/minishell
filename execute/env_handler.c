/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:58:16 by relamine          #+#    #+#             */
/*   Updated: 2024/08/16 00:42:56 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_and_export_status(char ***env, t_gc **l_gc, t_gc **lst)
{
    char **tmp_env;
    int g;

	tmp_env = *env;
	g = 0;
    while (tmp_env != NULL && tmp_env[g])
    {
        if (ft_strcmp(tmp_env[g], "@exitstatus") != 0 && tmp_env[g + 1] == NULL)
            ft_export_status(0, env, l_gc, lst);
        g++;
    }
}
int update_exitstatus(char ***envp, int status, t_gc **l_gc, t_gc **lst)
{
    int i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], "@exitstatus=", 12) == 0)
		{
			(*envp)[i] = ft_strjoin("@exitstatus=", ft_itoa(status, l_gc), lst);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export_status(int status, char ***envp, t_gc **l_gc, t_gc **lst)
{
	size_t	env_count;
	char	**new_env;
	int		i;

	if (update_exitstatus(envp, status, l_gc, lst))
		return;
	i = 0;
	env_count = ft_strlen_double(*envp);
	new_env = ft_malloc(sizeof(char *) * (env_count + 2), lst);
	while ((*envp)[i])
	{
		new_env[i] = ft_strdup((*envp)[i], lst);
		i++;
	}
	new_env[i] = ft_strjoin("@exitstatus=", ft_itoa(status, l_gc), lst);
	new_env[i + 1] = NULL;
	*envp = new_env;
}
