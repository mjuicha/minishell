/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:40:19 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/28 16:06:50 by mjuicha          ###   ########.fr       */
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
        if (ft_strncmp((*exp)->sub, tmp_env->var, ft_strlen((*exp)->sub)) == 0)
        {
            ((*exp)->res = ft_strdup(tmp_env->value));
            return (1);
        }
        tmp_env = tmp_env->next;
    }
    return (0);
}

void    show_exp(t_shell **shell)
{
    if (!(*shell)->exp)
        return ;
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
    (*i)++;
}

int    to_check(char *s, int i)
{
    while (ft_isalnum(s[i]) || ft_isalpha(s[i]) || s[i] == '_')
        i++;
    return (i);
}

void    check_nextt(char *s, int *n, t_shell **shell)
{
    (*n)++;
    int i = *n;
    t_exp *exp = malloc(sizeof(t_exp));
    int m;
    m = to_check(s, i);
    exp->sub = ft_substr(s, i, m - i);
    if (search(&exp, (*shell)->env_list) == 1)
    {
        printf("it is valid\n");
        printf("the value of %s is %s\n", exp->sub, exp->res);
    }
    else 
    {
        printf("your input is not valid ??\nREPEAT ;)\n");
    }
}

void    double_quote(char *s, int *n, t_shell **shell)
{
    int     i = *n;

    if (!s)
        return ;
    i++;
    while (s[i] && s[i] != DQ)
    {
        if (s[i] == DOLLAR)
            check_nextt(s, &i, shell);
        i++;
    }
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
    
    while (s[i])
    {
        if (s[i] == SQ)
            single_quote(s, &i);
        if (s[i] == DQ)
            double_quote(s, &i, shell);
        i++;
    }
    show_exp(shell);
    return (NULL);
}

char    *start_expand(char *s, t_shell **shell)
{
    if (!s || !shell)
        return (NULL);

    if (ft_strchr(s, DOLLAR))
    {
         valid_status(s, shell) ;
         
        
            // return (expand_var(s, shell));
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