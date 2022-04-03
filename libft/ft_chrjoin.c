/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 20:49:32 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 15:57:41 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_chrjoin(char *s1, char s2)
{
	char	*tmp;
	long	i;

	i = -1;
	if (s1)
	{
		tmp = malloc(sizeof(char) * ((ft_strlen(s1) + 2)));
		if (!tmp)
			error_end(3);
		while (s1[++i])
			tmp[i] = s1[i];
		tmp[i] = s2;
		tmp[i + 1] = '\0';
		free (s1);
	}
	else
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			error_end(3);
		tmp[0] = s2;
		tmp[1] = '\0';
	}
	return (tmp);
}

char	*ft_chrjoin_f(char *s1, char s2)
{
	char	*tmp;
	long	i;
	long	a;

	i = 0;
	a = -1;
	if (s1)
	{
		tmp = ft_calloc(sizeof(char), (ft_strlen(s1) + 2));
		tmp[i] = s2;
		while (s1[++a] && ++i)
			tmp[i] = s1[a];
		tmp[++i] = '\0';
		free (s1);
	}
	else
	{
		tmp = malloc(sizeof(char) * 2);
		if (!tmp)
			error_end(3);
		tmp[0] = s2;
		tmp[1] = '\0';
	}
	return (tmp);
}
