/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 10:57:22 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/10 04:38:19 by mjuicha          ###   ########.fr       */
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
# define DQ     34
# define SQ     39
# define RI     60
# define RO     62
# define PP     124
# define WORD   27
# define HERDOC   28
# define APPEND   29
typedef struct s_env
{
    char            *env;
    char            *var;
    char            *value;
    struct s_env    *next;
}                   t_env;

typedef struct s_token
{
    char            *token_name;
    int             type;
    struct s_token  *next;
}                   t_token;

typedef struct s_shell
{
    char    *line;
    t_env   *env_list;
    t_token *token;
}           t_shell;

void	display_prompt(void);
char    *ft_handle_signals(void);
void    ft_parser(char *line);
int     ft_lexer(t_shell **shell);
int     empty(char *line);
t_env   *ft_init_env(char **env);
void    ft_init_shell(t_shell **shell, char **env);
t_token     *ft_tokenizer(char *line);
// void    show_env(t_env *env_list);

#endif
