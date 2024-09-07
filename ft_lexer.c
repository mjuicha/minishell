/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:10:17 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/06 22:16:33 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//handling a|||a
int ft_syntax_error(char *error)
{
    ft_putstr_fd("minishell: syntax error near unexpected token '", 2);
    ft_putstr_fd(error, 2);
    ft_putendl_fd("'", 2);
    return (1);
}
int ft_three_pipes_ampersand(char *line)
{
    int i;

    i = 0;
    while (line[i + 3])
    {
        if (line[i] != '|' && line[i + 1] == '|' && line[i + 2] == '|' && line[i + 3] == '|' && line[i + 4] != '|')
            return (ft_syntax_error("|"));
        i++;
    }
    i = 0;
    while (line[i + 3])
    {
        if (line[i] != '&' && line[i + 1] == '&' && line[i + 2] == '&' && line[i + 3] == '&' && line[i + 4] != '&')
            return (ft_syntax_error("&"));
        i++;
    }
    return (0);
}

/*
;;
"a|a" 
||
"a&a"
&&
&a
*/
int ft_pipes_ampersand_semicolons_errors(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == ';' && line[i + 1] == ';')
            return (ft_syntax_error(";;"));
        if (line[i] == '|' && line[i + 1] == '|')
            return (ft_syntax_error("||"));
        if (line[i] == '&' && line[i + 1] == '&')
            return (ft_syntax_error("&&"));
        i++;
    }
    return (0);
}

int ft_pipes_ampersand_chaining_errors(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '|' && line[i + 1] == '|' && line[i] != '|')
            return (1);
        if (line[i] != '&' && line[i + 1] == '&' && line[i] != '&')
            return (1);
        i++;
    }
    return (0);
}

int ft_lexer(char *line)
{
    if (ft_three_pipes_ampersand(line))
        return (1);
    if (ft_pipes_ampersand_semicolons_errors(line) == 1)
        return (1);
    if (ft_pipes_ampersand_chaining_errors(line) == 1)
        return (0);
    return (0);
}