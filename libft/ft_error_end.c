/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:45:19 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 18:04:47 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	error_end(int flag)
{
	t_malloc_c	*tmp;

	tmp = save_point(NULL, 0);
	clear_point(tmp);
	if (flag == 0)
		exit (0);
	if (flag == 1)
	{
		printf ("Error: atoi/incorrect argument\n");
		exit (1);
	}
	if (flag == 2)
	{
		printf ("Error: parse error\n");
		exit (1);
	}
	if (flag == 3)
	{
		printf ("Error: malloc error\n");
		exit (1);
	}
}
