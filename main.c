/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:30 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/07 18:10:30 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*env_list;

	(void)ac;
	(void)av;
	env_list = NULL;
	ft_init_env(&env_list, env);
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
