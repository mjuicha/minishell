/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:16:37 by mjuicha           #+#    #+#             */
/*   Updated: 2023/12/06 20:43:58 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_size(long int n)
{
	long int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			s;
	int			i;
	long int	num;

	i = count_size(n);
	num = n;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	s = i - 1;
	if (num == 0)
		str[s] = '0';
	while (s >= 0 && num != 0)
	{
		str[s--] = (num % 10) + '0';
		num = num / 10;
	}
	str[i] = '\0';
	return (str);
}
