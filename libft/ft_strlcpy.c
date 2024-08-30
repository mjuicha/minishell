/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:44:55 by mjuicha           #+#    #+#             */
/*   Updated: 2023/11/22 22:56:28 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	x;

	src_len = ft_strlen(src);
	x = 0;
	if (dstsize > 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			dest[x] = src[x];
			x++;
		}
		dest[x] = '\0';
	}
	return (src_len);
}
