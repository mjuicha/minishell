/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:17:53 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/24 15:17:08 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_token(t_token **token)
{
    t_token *tmp;
    if (!token)
        return ;

    tmp = *token;
    while (tmp)
    {
        free(tmp->token_name);
        tmp = tmp->next;
    }
    tmp = *token;
    while (tmp)
    {
        *token = tmp->next;
        free(tmp);
        tmp = *token;
    }
}

void    ft_reset(t_shell **shell)
{
    free_token(&(*shell)->token);
}