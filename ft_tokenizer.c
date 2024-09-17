/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:20:52 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/17 12:24:26 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     nospec(char c)
{
    if (c == PP || c == RI || c == RO || c == HERDOC || c == APPEND || c == ' ' || c == '\t' || c == 0)
        return (0);
    return (1);
}

void    check_quotes(char *line, int *i)
{
    char fin;
    fin = line[*i];
    if (line[*i] == DQ || line[*i] == SQ)
    {
        (*i)++;
        while (line[*i] && line[*i] != fin)
            (*i)++;
        (*i)++;
    }
    else if (line[*i] && nospec(line[*i]))//g"
    {
        (*i)++;
        check_quotes(line, i);
    }
    // if (line[*i] && nospec(line[*i + 1]))
    //     check_quotes(line, i);
    // if (line[*i] == DQ || line[*i] == SQ)
    //     check_quotes(line, i);
}

int     count_malloc(char *line, int i, int start)
{
    int x;
    int res;
    char quote;
    int status;

    status = 0;
    res = 0;
    x = start;
    if (!line)
        return (0);
    while (line[x] && x < i)
    {
        if ((line[x] == DQ || line[x] == SQ) && status == 0)
        {
            quote = line[x];
            status = 1;
            x++;
        }
        if (quote == line[x] && status == 1)
        {
            quote = 0;
            status = 0;
        }
        if (!(line[x] == DQ || line[x] == SQ) || status == 1)
            res++;
        x++;
    }
    return (res);
}

char   to_quote(char *line, int i)
{
    while (line[i])
    {
        if (line[i] == DQ || line[i] == SQ)
            return (line[i]);
        i++;
    }
    return (0);
}

t_token    *get_quoted(char *line, int *i, int start)
{
    t_token *new = malloc(sizeof(t_token));
    char    quote;
    int     status;
    int     malloc;

    if (!line)
        return (NULL);
    quote = to_quote(line, *i);
    status = 0;

    malloc = 1;
    while (line[*i])
    {
        if (line[*i] == quote)
            status++;
        else if (!nospec(line[*i])  && status % 2 == 0)
            break ;
        (*i)++;
    }
    malloc = count_malloc(line, *i, start);
    new->token_name = ft_substr(line, start, malloc, quote);
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
    char fin;

    start = *i;
    while (line[*i])
    {
        if (line[*i] == ' ' || line[*i] == '\t' || line[*i] == DQ ||
            line[*i] == SQ || line[*i] == RI || line[*i] == RO || line[*i] == PP)
            break ;
        (*i)++;
    }
    fin = 0;
    if (line[*i] == DQ || line[*i] == SQ)
        fin = line[*i];
    check_quotes(line, i);
    new->token_name = ft_substr(line, start, *i - start, fin);
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
    int i = 12;
    while (tmp)
    {
        printf("[%d]%s\n",i, tmp->token_name);
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
            token = ft_tokenadd_back(token,get_quoted(line, &i, i));
        else if (line[i] == RI || line[i] == RO)
             token = ft_tokenadd_back(token, get_redirection(line, &i));
        else if (line[i] == PP)
            token = ft_tokenadd_back(token, get_pipe(line, &i));
        else
            token = ft_tokenadd_back(token, get_quoted(line, &i, i));
        // puts("hh");
    }
    show_token(token);
    return (token);
}