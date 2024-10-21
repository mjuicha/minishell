/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:40:19 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/21 18:07:56 by mjuicha          ###   ########.fr       */
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
    t_exp *exp = (*shell)->exp;
    if (!exp)
    {
        printf("no exp\n");
        return ;}
    puts("fd\n");
    while (exp)
    {
        printf("[%s]    ----->  {%s}\n", exp->sub, exp->res);
        printf("valid = %d\n", exp->valid);
        exp = exp->next;
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
    if (ft_isdigit(s[i]))
        return (++i);
    while (ft_isalnum(s[i]) || s[i] == '_')
        i++;
    return (i);
}

void    spec_exp(char *s, int *i, t_shell **shell)
{
    t_exp *exp = malloc(sizeof(t_exp));

    if (s[*i] == DOLLAR)
    {
        exp->res = ft_strdup("$");
        exp->valid = 1;
        exp->sub = ft_substr(s, *i, 1);
    }
    else if (s[*i] == QM)
    {
        exp->res = ft_strdup("?");
        exp->valid = 1;
        exp->sub = ft_substr(s, *i, 1);
    }
    else if (is_space(s[*i]))
    {
        exp->res = ft_strdup("$");
        exp->valid = 2;
        exp->sub = ft_strdup("$");
        // *i -= 1;
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
    exp_DOLLAR->valid = 2;
    exp_DOLLAR->next = NULL;
    return (exp_DOLLAR);
}
int     check_back_slash(char *s, int i)
{
    if (s[i - 2] == BS)
        return (1);
    return 0;
}
void    check_nextt(char *s, int *n, t_shell **shell, int mode)
{
    (*n)++;
    int i = *n;
    t_exp *exp = malloc(sizeof(t_exp));
    int m;
    m = to_check(s, i);
    if (check_back_slash(s, i))
    {
        exp->sub = ft_substr(s, i - 2, m - i + 2);
        exp->res = ft_substr(s, i - 1, m - i + 1);
        exp->valid = -1;
        exp->next = NULL;
        (*shell)->exp = ft_lstadd_backex((*shell)->exp, exp);
        *n = m;
        return ;
    }
    if (m == 0)
    {
        spec_exp(s, &i, shell);
        *n = i;
        return ;
    }
    if (m == i)
    {
        printf("i am here\n");
        exp = exp_DOLLAR();
        if ((s[i] == DQ || s[i] == SQ) && mode == 1)
            exp->valid = 0;
        *n = i;
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
        *n = i;
        return ;
    }
    while (s[i] && s[i] != DQ)
    {
        if (s[i] == DOLLAR)
        {
            check_nextt(s, &i, shell, 0);
        }
        // if (s[i] == DQ || s[i] == DOLLAR)
        //     continue;
        else
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
            check_nextt(s, &i, shell, 1);
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
    return (res + 1);
}

int count_malloc_exp(char *s, t_exp *exp)
{
    t_exp *mexp = exp;
    (void)s;
    if (!mexp)
        return (0);
    int plus = 0;
    int minus = 0;
    while (mexp)
    {
        if (mexp->valid  == 1 || mexp->valid == -1)
        {
            minus -= ft_strlen(mexp->sub);//in case of $= it will be 2 one for $ and one for = 
            if (mexp->valid == 1)
                minus -= 1;
            plus += ft_strlen(mexp->res);
        }
        else if (mexp->valid == 2)
        {
            plus += ft_strlen(mexp->res);
            minus -= (ft_strlen(mexp->sub));
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
    int x = 0;
    int xp = 0;
    int mallloc = 0;
    int quote = 0;
    int status = 0;
    exp = (*shell)->exp;
    mallloc = count_malloc_quote(s) + count_malloc_exp(s, (*shell)->exp);
    printf("mallloc = %d\n", mallloc);
    exp_str = malloc(sizeof(char) * mallloc + 1);
    i = 0;
    while (s[i])
    {
        if ((s[i] == DQ || s[i] == SQ) && status == 0)
        {
            quote = s[i];
            status = 1;
            i++;
        }
        if (s[i] == quote && status == 1)
        {
            quote = 0;
            status = 0;
        }
        if (!(s[i] == DQ || s[i] == SQ) || (status == 1))
        {
            if (s[i] == DOLLAR && exp)
            {
               while (s[i] == DOLLAR && exp)
               {
                    if (exp->valid == 1)
                    {
                        xp = 0;
                        i += ft_strlen(exp->sub);
                        while (exp->res[xp])
                        {
                            exp_str[x] = exp->res[xp];
                            xp++;
                            x++;
                        }
                    }
                    else if (exp->valid == -1)
                    {
                        xp = 0;
                        while (exp->res[xp])
                        {   
                            exp_str[x] = exp->res[xp];
                            xp++;
                            x++;
                        }
                        i = i + ft_strlen(exp->sub) - 1;
                    }
                    else if(exp->valid == 2)
                    {
                        xp = 0;
                        while (exp->res[xp])
                        {
                            exp_str[x] = exp->res[xp];
                            xp++;
                            x++;
                        }
                        exp = exp->next;
                        break;
                    }
                    else
                        i = i + ft_strlen(exp->sub);
                    exp = exp->next;
               }
            }
            else
            {
                if (s[i] == BS && s[i + 1] == DOLLAR)
                    {}
                else
                {
                    exp_str[x] = s[i];
                    x++;
                }
            }
        }
        if (s[i] == 0)
            break ;
        i++;
    }
    exp_str[x] = '\0';
    printf("[string]----->  [\x1b[31;1m%s\x1b[0m]\n", exp_str);//\x1b[32;1m➜\x1b[35;1m  minishell $\x1b[0m // for Red is 
    free((*shell)->exp);
    (*shell)->exp = NULL;
    return (exp_str);
}

char    *start_expand(char *s, t_shell **shell)
{
    if (!s || !shell)
        return (NULL);
    // char *string = ft_strdup(s);

    if (ft_strchr(s, DOLLAR))
    {
         valid_status(s, shell) ;
        //  free(s);
        // /*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*///**//**/
            // return (expand_var(s, shell));/**/
    }
    return (expand_var(s, shell));
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