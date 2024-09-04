/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/04 11:18:59 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

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


	(void)ac;
	(void)av;
	while (1)
	{
		line = handle_signals();
		if (line && ft_strlen(line) > 0)
			free(line);
		add_history(line);
	}
}
