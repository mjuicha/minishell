/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/22 16:54:24 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void ll(void)
{
	system("leaks minishell");
}
void    end_of_line(t_shell **shell);

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;

	(void)ac;
	(void)av;
	ft_init_shell(&shell, env);
	while (1)
	{
		shell->line = ft_handle_signals(&shell);
		if (empty(shell->line))
			continue ;
		add_history(shell->line);
		if (ft_lexer(&shell) == 1)
		{
			free(shell->line);
			continue ;
		}
		ft_parser(shell->line);
		if (shell->line)
			free(shell->line);
		ft_reset(&shell);
	}
	return (0);
}
