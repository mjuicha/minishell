/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:52:31 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/09 18:47:53 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_heredoc(t_shell **shell)
{
    t_token *token;

    int i = 0;
    token = (*shell)->token;
    if (!token)
        return (0);
    while (token->next)
    {
        if (token->type == HERDOC && token->next->type == WORD)
        {
            printf("heredoc: \x1b[33;1m%s\x1b[0m\n", token->token_name);
            printf("heredoc: %s\n", token->next->token_name);
            i++;
        }
        else
            break ;
        token = token->next;
        if (token->next)
            token = token->next;
        else
            break ;
    }
    return (i);
}

void show_array(char **arr)
{
    int i = 0;
    if (!arr)
        return ;
    while (arr[i])
    {
        printf("THE ARRAY[%d]:  \x1b[33;1m%s\x1b[0m\n",i, arr[i]);
        i++;
    }
}
void ft_heredoc(t_shell **shell)
{
    int i;
    i = count_heredoc(shell);
    char **array = malloc(sizeof(char *) * (i + 1));
    if (!array)
        return ;
    i = 0;
    t_token *token = (*shell)->token;
    if (!token)
        return ;
    while (token)
    {
        if (token->type == HERDOC && token->next)
        {
            token = token->next;
            if (token->type == WORD)
            {
                array[i] = ft_strdup(token->token_name);
                printf("leeet   : \x1b[33;1m%s\x1b[0m\n", array[i]);
                i++;
            }
        }
         token = token->next;   
    }
    array[i] = NULL;
    show_array(array);
}