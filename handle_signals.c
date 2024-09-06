/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:14:23 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/06 21:41:18 by mjuicha          ###   ########.fr       */
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
void    l(void)
{
    system("leaks minishell");
}

void    end_of_line(void)
{
    ft_putstr_fd("\033[A\033[K", 2);
    ft_putstr_fd("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ", 2);
    ft_putendl_fd("exit", 2);
    exit(EXIT_SUCCESS);
}

char    *ft_handle_signals(void)
{
    char    *line;

    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    rl_catch_signals = 0;
	line = readline("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ");
    if (!line)
        end_of_line();
    return (line);
}