/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 00:44:54 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/10 01:18:13 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_init_shell(t_shell **shell, char **env)
{
    *shell = NULL;
    *shell = malloc(sizeof(shell));
    if (!*shell)
        return ;
	(*shell)->env_list = ft_init_env(env);
    // show_env((*shell)->env_list);
}