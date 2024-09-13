/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:44:55 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/13 22:45:57 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize, char fin)
{
	size_t	src_len;
	size_t	x;
	size_t	i;

	src_len = ft_strlen(src);
	x = 0;
	i = 0;
	if (dstsize > 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			if (src[i] == fin)
				i++;
			dest[x] = src[i];
			i++;
			x++;
		}
		dest[x] = '\0';
	}
	return (src_len);
}
