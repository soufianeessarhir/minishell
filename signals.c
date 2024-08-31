/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:02:28 by relamine          #+#    #+#             */
/*   Updated: 2024/08/31 01:34:05 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_a.exitstatus_singnal = 1;
		if (g_a.stpsignal_inparent == 1)
			return ;
		if (g_a.stphedorc_insgin == 1)
		{
			g_a.stphedorc_insgin = 2;
			printf("\n");
			close(0);
			close(1);
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	white_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	setting_term(struct termios *term, struct termios *term_orig)
{
	tcgetattr(STDIN_FILENO, term);
	*term_orig = *term;
	tcsetattr(STDIN_FILENO, TCSANOW, term);
}
