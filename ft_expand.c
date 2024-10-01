/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:40:19 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/01 16:35:16 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exp   *ft_lstadd_backex(t_exp *exp, t_exp *new)
{
    t_exp *tmp;
    if (!new)
        return (NULL);
    if (!exp)
        exp = new;
    else 
    {
        tmp = exp;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
    return (exp);
}

int search(t_exp **exp, t_env *env)
{
    t_env *tmp_env = env;
    if (!exp || !env)
        return (0);
    while (tmp_env)
    {
        if (ft_strncmp((*exp)->sub, tmp_env->var, ft_strlen((*exp)->sub) + 1) == 0)
        {
            ((*exp)->res = ft_strdup(tmp_env->value));
            (*exp)->valid = 1;
            (*exp)->next = NULL;
            return (1);
        }
        
        tmp_env = tmp_env->next;
    }
    (*exp)->res = NULL;
    (*exp)->valid = 0;
    (*exp)->next = NULL;
    return (0);
}

void    show_exp(t_shell **shell)
{
    if (!(*shell)->exp)
    {
        printf("no exp\n");
        return ;}
    puts("fd\n");
    while ((*shell)->exp)
    {
        printf("[%s]    ----->  {%s}\n", (*shell)->exp->sub, (*shell)->exp->res);
        (*shell)->exp = (*shell)->exp->next;
    }
}

// char *valid_status(char *s, t_shell **shell)
// {
//     int i = 0;
//     int start;
//     t_exp *exp;
//     if (!s || !shell)
//         return (NULL);
//     while (s[i])
//     {
//         if (s[i] == DOLLAR)
//         {
//             start = ++i;
//             while (s[i] && (isalnum(s[i]) || s[i] == '_'))
//                 i++;
//             if (start == i)
//                 break ;
//                     exp = malloc(sizeof(t_exp));
//             exp->sub = ft_substr(s,start, i - start, 0);
//             exp->next = NULL;
//             if (search(&exp, (*shell)->env_list))
//                 ft_lstadd_backex((*shell)->exp, exp);
//         }
//         i++;
//     }
//     show_exp(shell);
//     return (NULL);
// }
        // if (s[i] == DOLLAR)
        // {
        //     start = ++i;
        //     while (s[i] && s[i] != '\n')
        //         i++;
        //     if (start == i)
        //         break ;
                
        //     exp = malloc(sizeof(t_exp));
        //     exp->sub = ft_substr(s,start, i - start);
        //     exp->next = NULL;
        //     if (search(&exp, (*shell)->env_list))
        //         ft_lstadd_backex((*shell)->exp, exp);
        //     free(exp->res);
        //     free(exp->sub);
        // }
        // i++;
void    single_quote(char *s, int *i)
{
    if (!s)
        return ;
    (*i)++;
    while (s[*i] && s[*i] != SQ)
        (*i)++;
    if (s[*i] == SQ)
        (*i)++;
}

int is_space(char c)
{
    if ((c >= 9 && c <= 13) || c == 32)
        return (1);
    return (0);
}

int    to_check(char *s, int i)
{
    if (s[i] == DOLLAR || s[i] == QM || is_space(s[i]))
        return (0);
    while (ft_isalnum(s[i]) || s[i] == '_')
        i++;
    return (i);
}

void    spec_exp(char *s, int *i, t_shell **shell)
{
    t_exp *exp = malloc(sizeof(t_exp));
    
    exp->sub = ft_substr(s, *i, 1);
    if (s[*i] == DOLLAR)
    {
        exp->res = ft_strdup("$");
        exp->valid = 1;
    }
    else if (s[*i] == QM)
    {
        exp->res = ft_strdup("?");
        exp->valid = 1;
    }
    else if (is_space(s[*i]))
    {
        exp->res = ft_strdup("$");
        exp->valid = 1;
    }
    exp->next = NULL;
    *i += 1;
    (*shell)->exp = ft_lstadd_backex((*shell)->exp, exp);
}

t_exp   *exp_DOLLAR(void)
{
    t_exp *exp_DOLLAR;

    exp_DOLLAR = malloc(sizeof(t_exp));
    exp_DOLLAR->sub = ft_strdup("$");
    exp_DOLLAR->res = ft_strdup("$");
    exp_DOLLAR->valid = 1;
    exp_DOLLAR->next = NULL;
    return (exp_DOLLAR);
}
void    check_nextt(char *s, int *n, t_shell **shell)
{
    (*n)++;
    int i = *n;
    t_exp *exp = malloc(sizeof(t_exp));
    int m;
    m = to_check(s, i);
    if (m == 0)
    {
        spec_exp(s, &i, shell);
        return ;
    }
    
    if (m == i)
    {
        exp = exp_DOLLAR();
        *n = i + 1;
        (*shell)->exp = ft_lstadd_backex((*shell)->exp, exp);
        return ;
    }
    exp->sub = ft_substr(s, i, m - i);
    *n = m;
    search(&exp, (*shell)->env_list);
    (*shell)->exp = ft_lstadd_backex((*shell)->exp, exp);
}

void    double_quote(char *s, int *n, t_shell **shell)
{
    int     i = *n;

    if (!s)
        return ;
    i++;
    if (s[i] == DQ)
    {
        i++;
        return ;
    }
    while (s[i] && s[i] != DQ)
    {
        if (s[i] == DOLLAR)
            check_nextt(s, &i, shell);
        if (s[i] == DQ || s[i] == DOLLAR)
            continue;
        i++;
    }
    if (s[i] == DQ)
        i++;
    *n = i;
}

void    simple_word(char *s, int *n, t_shell **shell)
{
    int i = *n;
    if (!s)
        return ;
    while (s[i] && s[i] != DQ && s[i] != SQ)
    {
        if (s[i] == DOLLAR)
            check_nextt(s, &i, shell);
        if (s[i] == DQ || s[i] == SQ)
            break ;
        if (s[i] == DOLLAR)
            continue ;
        i++;
    }
    *n = i;
}

char    *valid_status(char *s, t_shell **shell)
{
    int i = 0;
    // int start;
    // int status = 0;
    // int mode = 1;
    // (void)exp;
    if (!s || !shell)
        return (NULL);
    (*shell)->exp = NULL;
    while (s[i])
    {
        if (s[i] == SQ)
            single_quote(s, &i);
        if (s[i] == DQ)
            double_quote(s, &i, shell);
        else
            simple_word(s, &i, shell);
    }
    show_exp(shell);
    return (NULL);
}

int count_malloc_quote(char *s)
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
        if (!(s[i] == DQ || s[i] == SQ) || status == 1)
            res++;
        i++;
    }
}

int count_malloc_exp(char *s, t_exp *exp)
{
    t_exp *mexp = exp;
    if (!mexp)
        return (0);
    int plus = 0;
    int minus = 0;
    while (mexp)
    {
        if (mexp->valid  == 1)
        {
            minus -= (ft_strlen(mexp->sub) + 1);
            plus += ft_strlen(mexp->res);
        }
        else
            minus -= (ft_strlen(mexp->sub) + 1);
        mexp = mexp->next;
    }
    return (minus + plus);
}

char    *expand_var(char *s, t_shell **shell)
{
    t_exp *exp;
    char *exp_str;
    int i;
    int malloc = 0;
    exp = (*shell)->exp;
    malloc = count_malloc_quote(s) + count_malloc_exp(s, (*shell)->exp);
    i = 0;
    while (s[i])
    {
        
    }
}

char    *start_expand(char *s, t_shell **shell)
{
    if (!s || !shell)
        return (NULL);
    char *string = ft_strdup(s);

    if (ft_strchr(s, DOLLAR))
    {
         valid_status(s, shell) ;
         free(s);
         return (expand_var(string, shell));
        // /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*///**//**/
            // return (expand_var(s, shell));/**/
    }
    return (s);
}

void    ft_expand(t_shell **shell)
{
    t_token *token = (*shell)->token;

    if (!token)
        return ;
    while (token)
    {
        if (token->type == WORD)
            token->token_name = start_expand(token->token_name, shell);
        token = token->next;
    }
}