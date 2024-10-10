/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:52:31 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/10 20:11:35 by mjuicha          ###   ########.fr       */
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
    while (token && token->type != HERDOC)
        token = token->next;
    if (!token)
        return (0);
    while (token && token->next)
    {
        if (token->type == HERDOC && token->next->type == WORD)
        {
            token = token->next;
            i++;
            if (token->next)
                token = token->next;
        }
        else
            break ;
    }
    printf("i: %d\n", i);
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
void    eof_heredoc(t_herd **herd)
{
    if (!herd || !(*herd)->del)
        return ;
    int i = 0;
    while ((*herd)->del[i])
    {
        free((*herd)->del[i]);
        i++;
    }
    (*herd)->exit = 1;
}

void    signal_heredoc(t_herd **herd)
{
    char *input;

    input = readline("> ");
    if (!input)
        eof_heredoc(herd);
    (*herd)->input = input;
}

void    riddance(char **array,t_herd **herd, int *i)
{
    if (array[*i] && !array[*i + 1])
        (*herd)->store = 1;
    else if (ft_strncmp(array[*i], (*herd)->input, ft_strlen((*herd)->input)) == 0)
        ++(*i);
}

void init_herd(t_herd **herd, char **array)
{
    (*herd) = malloc(sizeof(t_herd));
    (*herd)->del = array;
    (*herd)->exit = 0;
    (*herd)->store = 0;
    (*herd)->save = NULL;
}

t_save    *ft_lstnew_hd(char *s)
{
    t_save *new;

    new = malloc(sizeof(t_save));
    if (!new)
        return (NULL);
    new->str_save = ft_strdup(s);
    new->next = NULL;
    return (new);
}

void show_save(t_save *save)
{
    t_save *tmp = save;
    printf("hi\n");
    while (tmp)
    {
        printf("sasasasasasasa is >>>>>>> [%s]\n",tmp->str_save);
        tmp = tmp->next;
    }
}

void    ft_lstadd_back_hd(t_save **save, t_save *save_new)
{
    t_save *tmp;
    if (!save_new)
        return ;
    if (!(*save))
        *save = save_new;
    else
    {
        tmp = *save;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = save_new;
    }
}

void    store_input(t_herd **herd)
{
    if ((*herd)->store != 1)
        return ;
    ft_lstadd_back_hd(&(*herd)->save, ft_lstnew_hd((*herd)->input));
    
}

t_save    *start_implementation(char **array, t_shell **shell)
{
    t_herd *herd;
    init_herd(&herd, array);
    if (!herd)
        return (NULL);
    int i = 0;
    (void)shell;
    while (1)
    {
        signal_heredoc(&herd);
        if (herd->exit == 1)
            return (free(herd), NULL);
        riddance(herd->del, &herd, &i);
        if (herd->store == 1 && ft_strncmp(herd->input,herd->del[i], ft_strlen(herd->input)) == 0)
            return (free(herd), herd->save);
        store_input(&herd);
        free(herd->input);
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
                i++;
            }
        }
         token = token->next;
    }
    array[i] = NULL;
    show_array(array);
    (*shell)->save = start_implementation(array, shell);
    show_save((*shell)->save);
}