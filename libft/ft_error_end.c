/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_end.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:45:19 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 20:12:26 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* clear_point(tmp); after tmp init ??*/
void	error_end(int flag)
{
	t_malloc_c	*tmp;

	tmp = save_point(NULL, 0);
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
