/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:51:05 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/25 18:25:48 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error_msg(char *s)
{
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(s, 2);
        ft_putendl_fd("'", 2);
    return (1);    
}

int check_next(char c, t_token *token)
{
    if (c == RI || c == RO || c == HERDOC || c == APPEND)
    {
        if (token->next == NULL)
            return (error_msg("newline"));
        if (token->next->type == RI)
            return (error_msg("<"));
        if (token->next->type == RO)
            return (error_msg(">"));
        if (token->next->type == HERDOC)
            return (error_msg("<<"));
        if (token->next->type == APPEND)
            return (error_msg(">>"));
    }
    return (0);
}
int ft_check_init(t_token *token)
{
    if (!token)
        return (0);
    if (token->type == PP) 
    {
        if (token->next && token->next->type == PP)
            return(error_msg("||"));
        return(error_msg("|"));
    }
    if (token->type == WORD)
    {
        if (token->token_name[0] == ';')
        {
            if (token->token_name[1] == ';')
                return (error_msg(";;"));
            return (error_msg(";"));
        }
        if (token->token_name[0] == '&')
        {
            if (token->token_name[1] == '&')
                return (error_msg("&&"));
            return (error_msg("&"));
        }
    }
    if (check_next(token->type, token))
        return (1);
    return (0);
}

int one_of_them(t_token *token, int type)
{
    if (type == RI || type == RO || type == HERDOC || type == APPEND)
        return (1);
    if (type == PP || token->token_name[0] == ';' || token->token_name[0] == '&')
        return (2);
    return (0);
}

char *ft_strone(char *s)
{
    if (s[0] == ';')
    {
        if (s[1] == ';')
            return (";;");
        return (";");
    }
    if (s[0] == '&')
    {
        if (s[1] == '&')
            return ("&&");
        return ("&");
    }
    return (s);
}

int check_pipe(t_token *token)
{
    if (!token || !token->next || token->type != PP)
        return (0);
    if (token->type == PP && token->next->type == PP)
        return (error_msg("||"));
    return (0);
}
int check_syntax(t_token *token)
{
    if (!token)
        return (0);
    while (token)
    {
        if (one_of_them(token, token->type) == 1 && token->next == NULL)
            return (error_msg("newline"));
        if (one_of_them(token, token->type) == 2 && token->next == NULL)
        {
            if (token->type == PP)
                return (error_msg("|"));
            return (ft_strone(token->token_name), 1);
        }
        if (one_of_them(token, token->type) == 1 && token->next->type == PP)
            return (error_msg("|"));
        if (check_pipe(token))
            return (1);
        token = token->next;
    }
    return (0);
}

int syntax_error(t_token *token)
{
    t_token *tmp;

    tmp = token;
    if (ft_check_init(token))
        return (1);
    if (check_syntax(token))
        return (1);
    return (0);
}