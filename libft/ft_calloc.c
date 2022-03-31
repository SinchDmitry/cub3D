/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:30 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/26 21:29:32 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	tmp = malloc(size * count);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, size * count);
	return (tmp);
}

void	*ft_calloc_error_end(size_t count, size_t size, int push)
{
	void	*tmp;

	tmp = malloc(size * count);
	if (tmp == NULL)
		error_end(3);
	save_point(tmp, push);
	ft_bzero(tmp, size * count);
	return (tmp);
}
