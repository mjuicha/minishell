/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:10:17 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/28 17:47:31 by mjuicha          ###   ########.fr       */
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

// void    show_token(char **token)
// {
//     int i = 0;
//     while (token && token[i])
//     {
//         printf("%s\n", token[i]);
//         i++;
//     }    
// }

// char    **ft_tokenizer(char *line)
// {
//     char    **token = malloc(sizeof(char *) * 1000);
//     int i;
//     int j;
//     int a;
//     int ind;

//     i = 0;
//     a = 0;
//     while (line[i])
//     {
//         ind = 0;
//         while (line[i] == ' ')
//             i++;
//         j = 0;
//             token[a] = malloc(sizeof(char) * 1000);
//         while (line[i] && line[i] != ' ')
//         {
//             token[a][j++] = line[i++];
//             ind = 1;
//         }
//         if (ind == 1)
//             token[a][j] = '\0';
//         a++;
//     }
//     token[a] = NULL;
//     i = 0;
//     while (token && token[i])// 
//     {
//         printf("%s\n", token[i]);
//         i++;
//     } 
//     // show_token(token);
//     return (token);
// }
void    lk(void)
{
    system("leaks minishell");
}
int ft_lexer(t_shell **shell)
{
    (*shell)->token = ft_tokenizer((*shell)->line);
    if ((*shell)->token == NULL)
        return (1);
    // show_token((*shell)->token);
    if (syntax_error((*shell)->token))
    {
        ft_reset(shell);
        return (1);
    }
    ft_heredoc(shell);//tomorrow
    ft_expand(shell);
    ft_reset(shell);
        // ft_heredoc(shell);
    return (0);
}

