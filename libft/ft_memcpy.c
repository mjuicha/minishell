/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:02:12 by mjuicha           #+#    #+#             */
/*   Updated: 2023/11/30 08:41:49 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*str;

	if (!dst && !src)
		return (0);
	if (dst == src)
		return (dst);
	str = (char *)dst;
	while (n)
	{
		*(unsigned char *)str = *(unsigned char *)src;
		str++;
		src++;
		n--;
	}
	return (dst);
}
