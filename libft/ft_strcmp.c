/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:38 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 19:06:28 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*tmps1;
	unsigned char	*tmps2;

	tmps1 = (unsigned char *)s1;
	tmps2 = (unsigned char *)s2;
	i = -1;
	if (!s1 || !s2)
		return (0);
	while (tmps1[++i] || tmps2[i])
		if (tmps1[i] != tmps2[i])
			return (tmps1[i] - tmps2[i]);
	return (0);
}

int	ft_strcmp_rev(char *s1, char *s2)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(s2) - 1;
	while (j > -1)
	{
		if (i == -1)
			return (-1);
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		i--;
		j--;
	}
	return (0);
}
