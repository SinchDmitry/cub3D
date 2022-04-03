/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:30 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 23:37:25 by utygett          ###   ########.fr       */
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
	(void) push;
	tmp = malloc(size * count);
	if (tmp == NULL)
		error_end(3);
	save_point(tmp, push);
	ft_bzero(tmp, size * count);
	return (tmp);
}
