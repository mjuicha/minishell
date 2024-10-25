/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 12:14:23 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/25 10:36:18 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int sig)
{
    (void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
void    l(void)
{
    system("leaks minishell");
}

void    free_env(t_env **env_list)
{
    t_env   *tmp;
    
    if (!(*env_list))
        return ;
    tmp = *env_list;
    while (tmp)
    {
        free(tmp->env);
        free(tmp->var);
        free(tmp->value);
        tmp = tmp->next;
    }
    tmp = *env_list;
    while (tmp)
    {
        free(tmp);
        tmp = tmp->next;
    }
}

void    free_shell(t_shell **shell)
{
    if (!(shell))
        return ;
    free_env(&(*shell)->env_list);
    free(*shell);
    // free_token((*shell)->token);
}

void    end_of_line(t_shell **shell)
{
    ft_putstr_fd("\033[A\033[K", 2);
    ft_putstr_fd("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ", 2);
    ft_putendl_fd("exit", 2);
    free_shell(shell);
    printf("BEFORE FREE SHELL\n");
    // atexit(l);
    exit(EXIT_SUCCESS);
}

char    *ft_handle_signals(t_shell **shell)
{
    char    *line;

    signal(SIGINT, handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    rl_catch_signals = 0;
	line = readline("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ");
    if (!line)
        end_of_line(shell);
    return (line);
}