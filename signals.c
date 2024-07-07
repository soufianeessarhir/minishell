/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sessarhi <sessarhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:02:28 by relamine          #+#    #+#             */
/*   Updated: 2024/07/07 18:35:38 by sessarhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        // rl_replace_line("", 0);
        rl_redisplay();
    }
}
