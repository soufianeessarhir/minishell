/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 00:50:33 by relamine          #+#    #+#             */
/*   Updated: 2024/07/08 01:32:28 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(const char *argv, char **env)
{
	size_t len = strlen(argv);

    while (*env)
	{
        if (strncmp(*env, argv, len) == 0 && (*env)[len] == '=') {
			
			if (unlink(*env))
			{
				perror("unset");
				return;
			}
            return;
        }
        env++;
    }
}