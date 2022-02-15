/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:58:11 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/15 16:43:07 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t		i;
	char		*arr;

	i = 0;
	arr = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!arr)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	*ft_strdup_error_end(const char *s1)
{
	size_t		i;
	char		*arr;

	i = 0;
	arr = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!arr)
		error_end(3);
	save_point(arr, 1);
	while (i < ft_strlen(s1))
	{
		arr[i] = s1[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}
