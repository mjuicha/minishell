/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:14:23 by mjuicha           #+#    #+#             */
/*   Updated: 2024/08/31 18:47:16 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int sig)
{
    (void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void    end_of_line(void)
{
    ft_putendl_fd("exit", 2);
    exit(EXIT_SUCCESS);
}

char    *handle_signals(void)
{
    char    *line;

    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    rl_catch_signals = 0;
	line = readline("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ");
    if (line && ft_strlen(line) == 0)
        free(line);
    else if (!line)
        end_of_line();
    return (line);
}