/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuicha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:42:09 by mjuicha           #+#    #+#             */
/*   Updated: 2023/11/27 19:15:42 by mjuicha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isoverflow(long long int check, long long int res)
{
	if (res / 10 == check)
		return (0);
	return (1);
}

static int	is_sspace(const char *str, int *pt)
{
	int	i;
	int	retsi;

	i = 0;
	retsi = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			retsi *= -1;
		i++;
	}
	*pt = i;
	return (retsi);
}

int	ft_atoi(const char *str)
{
	long long int	r;
	int				s;
	long long int	check;
	int				i;

	r = 0;
	s = is_sspace(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = r;
		r = r * 10 + (str[i] - '0');
		if (isoverflow(check, r) == 1)
		{
			if (s == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	return (r * s);
}
