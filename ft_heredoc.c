/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:52:31 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/21 18:07:36 by mjuicha          ###   ########.fr       */
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
    if (!arr || !arr[0])
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

int *herd_flag(void)
{
    static int flag;
    
    return (&flag);
}

void    herd_sig(int sig)
{
    if (sig == SIGINT)
        *herd_flag() = 1;
    ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void    signal_heredoc(t_herd **herd)
{
    char *input = NULL;

    printf("hh\n");
    if (*herd_flag() == 0)
        input = readline("> ");
    if (!input || *herd_flag() == 1)
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

char *check_env(char *s, t_env **env)
{
    t_env *tmp = *env;

    if (!s || !env)
        return (NULL);
    if (ft_strncmp(s, "?", 2) == 0 || ft_strncmp(s, "$", 2) == 0)
        return (s);
    while (tmp)
    {
        if (ft_strncmp(s, tmp->var, ft_strlen(s) + 1) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

int valid_next(char *s, int *i)
{
    if (s[*i + 1] == DOLLAR || s[*i + 1] == QM)
        return (++(*i));
    return (0);
}
int count_malloc_headoc(char *s, t_shell **shell, t_exp **expp)
{
    t_env *env = (*shell)->env_list;
    t_exp *exp = NULL;
    t_exp *head = NULL;
    int i = 0;
    int x = 0;
    int res = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == DOLLAR)
        {
            x = i;
            while (s[i + 1] && (ft_isalnum(s[i + 1]) || s[i + 1] == '_'))
            {
                if (s[x + 1] && s[x] == DOLLAR && ft_isdigit(s[x + 1]))
                    {i++;break ;}
                i++;
            }
            if (x != i || valid_next(s, &i))
            {
                i++;
                if (exp)
                    free(exp);
                exp = malloc(sizeof(t_exp));
                exp->sub = ft_substr(s, x + 1, i - x - 1);
                exp->res = check_env(exp->sub, &env);
                exp->next = NULL;
                head = ft_lstadd_backex(head, exp);
                if (exp->res)
                    res += ft_strlen(exp->res);
                if (!s[i])
                    break ;
            }
        }
        i++;
        res++;
    }
    *expp = head;
    return (res + 1);
}

char *ft_expand_hd(char *s, t_shell **shell)
{
    int i = 0;
    int x = 0;
    t_exp *exp = NULL;
    char *res = malloc(sizeof(char) * (count_malloc_headoc(s, shell, &exp)));
    int m = 0;
    while (s[i])
    {
        if (s[i] == DOLLAR && exp)
        {
            i += ft_strlen(exp->sub) + 1;
            while (exp && exp->res && exp->res[m])
            {
                res[x] = exp->res[m];
                m++;
                x++;
            }
            exp = exp->next;
        }
        res[x] = s[i];
        x++;
        i++;
    }
    res[x] = '\0';
    return (res);
}

t_save    *ft_lstnew_hd(char *s, t_shell **shell)
{
    t_save *new;

    new = malloc(sizeof(t_save));
    if (!new)
        return (NULL);
    if ((*shell)->hd_flag == 1)
        new->str_save = ft_strdup(s);
    else
        new->str_save = ft_strdup(ft_expand_hd(s, shell));
    new->next = NULL;
    return (new);
}

void show_save(t_save *save)
{
    t_save *tmp = save;
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

void    store_input(t_herd **herd, t_shell **shell)
{
    if ((*herd)->store != 1)
        return ;
    ft_lstadd_back_hd(&(*herd)->save, ft_lstnew_hd((*herd)->input, shell));
    
}

int max(char *s1, char *s2)
{
    int x;
    int y;

    x = ft_strlen(s1);
    y = ft_strlen(s2);
    return (x >= y ? x : y);
}
t_save    *start_implementation(char **array, t_shell **shell)
{
    t_herd *herd;
    init_herd(&herd, array);
    if (!herd)
        return (NULL);
    int i = 0;
    (void)shell;
    *herd_flag() = 0;
    while (1)
    {
        signal_heredoc(&herd);
        // signal(SIGINT, herd_sig);
        if (herd->exit == 1 || *herd_flag() == 1 )
            return (free(herd), NULL);
        riddance(herd->del, &herd, &i);
        if (herd->store == 1 && ft_strncmp(herd->input,herd->del[i], max(herd->input, herd->del[i])) == 0)
            return (free(herd), herd->save);
        store_input(&herd, shell);
        free(herd->input);
    }
}

int count_malloc_quote_hd(char *s)
{
    int i = 0;
    int status = 0;
    int quote = 0;
    int res = 0; 
    while (s[i]) 
    { 
        if ((s[i] == DQ || s[i] == SQ) && status == 0)
        {
            quote = s[i];
            status = 1;
            i++;
        }
        if (quote == s[i] && status == 1)
        {
            quote = 0;
            status = 0;
        }
        if ((!(s[i] == DQ || s[i] == SQ) && !(s[i] == DOLLAR && (s[i + 1] == DQ || s[i + 1] == SQ) && status == 0)) || status == 1)
            res++;
        if (s[i] == DOLLAR && (s[i + 1] == DOLLAR))
        {res++;i++;}
        i++;
    }
    return (res + 1);
}
char    *ft_rm(char *s, t_shell **shell)
{
    int quote = 0;
    int status = 0;
    int i = 0;
    (*shell)->hd_flag = 0;
    char *res = malloc(sizeof(char) * (count_malloc_quote_hd(s)));
    printf("malloc herdoc = %d\n", count_malloc_quote_hd(s));
    int x = 0;
    while (s[i])
    {
        if ((s[i] == DQ || s[i] == SQ) && status == 0)
        {
            (*shell)->hd_flag = 1;
            quote = s[i];
            status = 1;
            i++;
        }
        if (quote == s[i] && status == 1)
        {
            quote = 0;
            status = 0;
        }
        if (((!(s[i] == DQ || s[i] == SQ) && !(s[i] == DOLLAR && (s[i + 1] == DQ || s[i + 1] == SQ) && status == 0))) || status == 1)
        {
            res[x] = s[i];
            x++;
            if (s[i] == DOLLAR && (s[i + 1] == DOLLAR))
                {res[x] = s[i];x++;i++;}
        }
        i++;
    }
    res[x] = '\0';
    return (res);
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
                array[i] = ft_strdup(ft_rm(token->token_name, shell));
                i++;
            }
        }
         token = token->next;
    }
    array[i] = NULL;
    show_array(array);
    if (array && array[0])
    {(*shell)->save = start_implementation(array, shell);
    show_save((*shell)->save);}
}