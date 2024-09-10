/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 15:04:00 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/10 02:55:17 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char    *fill_var(char *env)
{
    char    *str;
    int     i;

    if (!env)
        return (NULL);
    i = 0;
    while (env[i] && env[i] != '=')
        i++;
    str = malloc(sizeof(char) * (i + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (env[i] && env[i] != '=')
    {
        str[i] = env[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

char    *fill_value(char *env)
{
    char    *str;
    int     i;
    int     r;

    if (!env)
        return (NULL);
    i = 0;
   while (env[i] && env[i] != '=')
        i++;
    r = i + 1;
    while (env[i])
        i++;
    str = malloc(sizeof(char) * (i - r + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (env[r])
        str[i++] = env[r++];
    str[i] = '\0';
    return (str);
}

char    *fill_env(char *env)
{
    char    *str;
    int     i;

    i = 0;
    if (!env)
        return (NULL);
    str = malloc(sizeof(char) * (ft_strlen(env) + 1));
    if (!str)
        return (NULL);
    str = ft_strdup(env);
    return (str);
}

t_env    *ft_envnew(char *env)
{
    t_env    *new;

    new = malloc(sizeof(t_env));
    if (!new)
        return (NULL);
    new->env = fill_env(env);
    new->var = fill_var(env);
    new->value = fill_value(env);
    new->next = NULL;
    return (new);
}

t_env    *ft_envadd_back(t_env *env_list, t_env *new)
{
    t_env    *tmp;

    if (!new)
        return (NULL);
    if (!env_list)
    {
        env_list = new;
        return (env_list);
    }
    tmp = env_list;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
    return (env_list);
}

void    show_env(t_env *env_list)
{
    t_env    *tmp;

    tmp = env_list;
    while (tmp)
    {
        printf("%s\n", tmp->env);
        tmp = tmp->next;
    }
}

t_env    *ft_init_env(char **env)
{
    t_env   *env_list;

    env_list = NULL;
    int i;
    if (!env || !env[0])
        return (NULL);
    i = 0;
    while (env[i])
    {
        env_list = ft_envadd_back(env_list, ft_envnew(env[i]));
        i++;
    }
    // show_env(env_list);
    return (env_list);
}