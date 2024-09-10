/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:20:52 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/10 06:39:40 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token    *get_quoted(char *line, int *i)
{
    t_token *new = malloc(sizeof(t_token));
    char    fin;
    int ind;
    if (!line)
        return (NULL);
    // puts("hh");

    fin = line[*i];
    ind = ++(*i);
    while (line[*i] && line[*i] != fin)
        (*i)++;
    new->token_name = ft_substr(line, ind, *i - ind);
    (*i)++;
    new->type = WORD;
    new->next = NULL;
    return (new);
}

t_token    *get_redirection(char *line, int *i)
{
    t_token *new = malloc(sizeof(t_token));

    new->next = NULL;
    if (line[*i] == '<')
    {
        (*i)++;
        if (line[*i] == '<')
        {
            (*i)++;
            new->token_name = ft_strdup("<<");
            new->type = HERDOC;
            return (new);
        }
        new->token_name = ft_strdup("<");
        new->type = RI;
    }
    else if (line[*i] == '>')
    {
        (*i)++;
        if (line[*i] == '>')
        {
           (*i)++;
            new->token_name = ft_strdup(">>");
            new->type = APPEND;
            return (new);
        }
        new->token_name = ft_strdup(">");
        new->type = RO;
    }
    return (new);
}

t_token    *get_pipe(char *line, int *i)
{
    (void)line;
    t_token *new = malloc(sizeof(t_token));
      (*i)++;
        new->token_name = ft_strdup("|");
        new->type = PP;
        new->next = NULL;
        return (new);
}

t_token    *get_word(char *line, int *i)
{
    t_token *new = malloc(sizeof(t_token));
    int start;

    start = *i;
    while (line[*i])
    {
        if (line[*i] == ' ' || line[*i] == '\t' || line[*i] == DQ ||
            line[*i] == SQ || line[*i] == RI || line[*i] == RO || line[*i] == PP)
            break ;
        (*i)++;
    }
    new->token_name = ft_substr(line, start, *i - start);
    new->type = WORD;
    new->next = NULL;
     return (new);
}

t_token *ft_tokenadd_back(t_token *token, t_token *new)
{
    t_token *tmp;

    if (!new)
        return (NULL);
    if (!token)
    {
        token = new;
        return (token);
    }
    tmp = token;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (token);
}
void    show_token(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp)
    {
        printf("%s\n", tmp->token_name);
        tmp = tmp->next;
    }
}
t_token     *ft_tokenizer(char *line)
{
    t_token *token;
    int     i;
    token = NULL;
    if ( !line)
        return (NULL);

    i = 0;
    while (line[i])
    {
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == DQ || line[i] == SQ)
            token = ft_tokenadd_back(token,get_quoted(line, &i));
        if (line[i] == RI || line[i] == RO)
             token = ft_tokenadd_back(token, get_redirection(line, &i));
        if (line[i] == PP)
            token = ft_tokenadd_back(token, get_pipe(line, &i));
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        printf("[%s]\n", line);
        token = ft_tokenadd_back(token, get_word(line, &i));
        // puts("hh");
    }
    show_token(token);
    return (token);
}