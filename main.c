/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/06 21:42:20 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	main(int ac, char **av)
{
	char	*line;

	(void)ac;
	(void)av;
	while (1)
	{
		line = ft_handle_signals();
		if (empty(line))
			continue ;
		add_history(line);
		if (ft_lexer(line) == 1)
		{
			free(line);
			continue ;
		}
		ft_parser(line);
		if (line)
			free(line);
	}
}
