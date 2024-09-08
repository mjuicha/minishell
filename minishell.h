/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:22 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/08 11:47:35 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include "libft/libft.h"
#include <signal.h>

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define VAR    0
# define VALUE  1
typedef struct s_env
{
    char            *var;
    char            *value;
    struct s_env    *next;
}                   t_env;

void	display_prompt(void);
char    *ft_handle_signals(void);
void    ft_parser(char *line);
int     ft_lexer(char *line);
int     empty(char *line);
t_env   *ft_init_env(t_env *env_list, char **env);

#endif
