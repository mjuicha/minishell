/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:44:55 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/21 18:12:13 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize, char quote)
{
	size_t	src_len;
	size_t	x;
	size_t	i;
	int		status;

	status = 0;
	quote = 0;
	src_len = ft_strlen(src);
	x = 0;
	i = 0;
	if (dstsize > 0)
	{
		while (src[x] && x < (dstsize - 1))
		{
			if ((src[i] == DQ || src[i] == SQ) && status == 0)
			{
				quote = src[i];
				status = 1;
				i++;
			}
			if (src[i] == quote && status == 1)
			{
				quote = 0;
				status = 0;
			}
			if (!(src[i] == DQ || src[i] == SQ) || status == 1)
			{
				dest[x] = src[i];
				x++;
			}
			i++;
		}
		dest[x] = '\0';
	}
	return (src_len);
}
