/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 20:55:46 by mjuicha           #+#    #+#             */
/*   Updated: 2023/11/26 12:18:14 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*memory;
	size_t	other;

	other = count * size;
	if (size != 0 && other / size != count)
		return (NULL);
	memory = malloc(other);
	if (memory == NULL)
		return (0);
	ft_bzero(memory, other);
	return (memory);
}
