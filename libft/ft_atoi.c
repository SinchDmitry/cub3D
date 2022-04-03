/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:23:14 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 00:06:06 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_overflow_int(long res, int sign)
{
	if (res > 2147483647 && sign == -1)
		error_end (1);
	else if (res > 2147483648 && sign == 1)
		error_end (1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		a;
	long	res;

	i = 0;
	a = -1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			a = -a;
	if (str[i] >= 48 && str[i] <= 57)
	{
		while (str[i] >= 48 && str[i] <= 57 && str[i] != 32)
			res = res * 10 - (str[i++] - '0');
		if (str[i] && str[i] != 32)
			error_end (1);
	}
	else
		error_end (1);
	check_overflow_int(res, a);
	return (a * (int)res);
}
