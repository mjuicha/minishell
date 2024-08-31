/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/08/31 18:44:56 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>


void	display_prompt(void)
{
	// ft_putstr_fd("\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m ", 1);
}

char	*take_input(void)
{
	char	*line;

	line = readline(NULL);
	if (line && *line)
		add_history(line);
	free(line);
	return (line);
}

int	main(int ac, char **av)
{
	char	*line;

	while (1)
	{
		display_prompt();
		line = handle_signals();
	}
}
