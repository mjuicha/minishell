/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 01:20:52 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/31 17:38:06 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     nospec(char c)
{
    if (c == PP || c == RI || c == RO || c == ' ' || (c >= 9 && c <= 13) || c == 0)
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
    int c;// check empty space

    res = 0;
    c = start;
    x = start;
    if (!line)
        return (0);
    while (line[x] && x < i)
    {
        res++;
        x++;
    }
    return (res);
}

char   to_quote(char *line, int i)
{
    if (!line)
        return (0);
    while (line[i])
    {
        if (line[i] == DQ || line[i] == SQ)
            return (line[i]);
        i++;
    }
    return (0);
}

t_token    *get_quoted(char *line, int *i, int start, int *status)
{
    char    quote;
    int     mallloc;
    t_token *new;
    if (!line)
        return (NULL);
    quote = to_quote(line, *i);
    *status = 0;

    mallloc = 1;
    while (line[*i])
    {
        if (line[*i] == SQ || line[*i] == DQ)
        {
            if (*status % 2 == 0 || line[*i] == quote)
            {
                (*status)++;
                quote = line[*i];
            }
        }
        else if (!nospec(line[*i])  && (*status) % 2 == 0)//invalid " " && CLOSED QUOTE
            break ;
        (*i)++;
    }
    mallloc = count_malloc(line, *i, start);
    new = malloc(sizeof(t_token));
    
    if (!new)
        return (NULL);
    new->token_name = ft_substr(line, start, mallloc);
    // printf("malloc = %d\n", mallloc);
    // printf("new->token_name = [%s]\n", new->token_name);
    new->type = WORD;
    new->next = NULL;
    return (new);
}

t_token    *get_redirection(char *line, int *i)
{
    if (!line)
        return (NULL);
    t_token *new = malloc(sizeof(t_token));
    
    if (!new)
        return (NULL);
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

t_token    *get_pipe(int *i)
{
    t_token *new = malloc(sizeof(t_token));
    
    if (!new)
        return (NULL);
    (*i)++;
    new->token_name = ft_strdup("|");
    new->type = PP;
    new->next = NULL;
    return (new);
}

t_token    *get_word(char *line, int *i)
{
    t_token *new = malloc(sizeof(t_token));
    
    if (!new)
        return (NULL);
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
    if (!token)
        return ;
    tmp = token;
    int i = 12;
    while (tmp)
    {
        printf("[%d]%s\n",i, tmp->token_name);
        tmp = tmp->next;
    }
}

void    *quote_msg_error(t_token *token)
{
    t_token *tmp;

    tmp = token;
    while (tmp)
    {
        free(tmp->token_name);
        tmp = tmp->next;
    }
    tmp = token;
    while (tmp)
    {
        free(tmp);
        tmp = tmp->next;
    }
    printf("minishell: syntax error: unclosed quotes\n");
    return (NULL);
}

t_token     *ft_tokenizer(char *line)
{
    t_token *token;
    int     i;
    int     status;

    token = NULL;
    if (!line)
        return (NULL);
    i = 0;
    status = 0;
    while (line[i])
    {
        while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
            i++;
        if (line[i] == DQ || line[i] == SQ)
            token = ft_tokenadd_back(token,get_quoted(line, &i, i, &status));
        else if (line[i] == RI || line[i] == RO)
             token = ft_tokenadd_back(token, get_redirection(line, &i));
        else if (line[i] == PP)
            token = ft_tokenadd_back(token, get_pipe(&i));
        else if (line[i] == 0)
            break ;
        else
            token = ft_tokenadd_back(token, get_quoted(line, &i, i, &status));
    }
    if (status % 2 != 0)
        return (quote_msg_error(token));
    // show_token(token);
    return (token);
}