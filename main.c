/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/08/30 20:29:34 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>


void	display_prompt(void)
{
	ft_putstr_fd("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ", 1);
}

void handler(int sig)
{
	ft_putchar_fd('\n', 1);
	display_prompt();
}
int	main(int ac, char **av)
{
	display_prompt();
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	char *line=readline("");
	printf("%s",line);
	while (1)
	{
		// main(ac,av);
	}
}
