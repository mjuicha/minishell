/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:06:13 by mjuicha           #+#    #+#             */
/*   Updated: 2024/11/01 19:15:21 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_fd_manager(t_shell *shell)
{
    t_token *token;
    int fd_in;
    int fd_out;

    fd_in = 0;
    fd_out = 1;
    token = shell->token;
    while (token)
    {
        if (token->type == RI && token->next == WORD)
        {
            fd_in = open(token->next->token_name, O_RDONLY);
            close(fd_in);
        }
        if (token->type == RO && token->next == WORD)
        {
            fd_out = open(token->next->token_name, O_RDONLY);
            close(fd_out);
        }
    }
    //f<f<
}