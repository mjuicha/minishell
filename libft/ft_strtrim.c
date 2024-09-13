/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <mjuicha@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:13:39 by mjuicha           #+#    #+#             */
/*   Updated: 2024/09/13 21:04:18 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	while (s1)
	{
		if (ft_char_in_set(((char)*s1), set) == 1)
			s1++;
		else
			break ;
	}
	size = ft_strlen(s1);
	while (size != 0)
	{
		if (ft_char_in_set(s1[size - 1], set) == 1)
			size--;
		else
			break ;
	}
	str = (char *)malloc(size * sizeof(char) + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, size + 1, '\0');
	return (str);
}
