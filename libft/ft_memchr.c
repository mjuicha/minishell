/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 14:11:36 by mjuicha           #+#    #+#             */
/*   Updated: 2023/12/01 15:49:41 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*occ;

	occ = (unsigned char *)s;
	while (n--)
	{
		if (*occ == (unsigned char)c)
			return (occ);
		occ++;
	}
	return (NULL);
}
