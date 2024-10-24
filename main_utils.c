/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:36:45 by mjuicha           #+#    #+#             */
/*   Updated: 2024/10/24 15:10:55 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int empty(char *line)
{
    if (!line)
        return (0);
    if (ft_strlen(line) == 0)
        return (free(line), 1);
    return (0);
}