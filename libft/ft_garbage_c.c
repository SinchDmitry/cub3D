/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:47:26 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 16:37:51 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	save_type(t_malloc_c **head, t_malloc_c *new, int flag)
{
	t_malloc_c	*tmp;

	tmp = NULL;
	if (!*head)
		*head = new;
	else if (flag == 2)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else if (flag == 1)
	{
		new->next = *head;
		*head = new;
	}
}

t_malloc_c	*save_point(void *mal_p, int flag)
{
	static t_malloc_c	*head;
	t_malloc_c			*new;

	if (!flag)
		return (head);
	if (!mal_p)
	{
		head = NULL;
		return (head);
	}
	new = malloc(sizeof(t_malloc_c));
	if (!new)
		error_end(3);
	*new = (t_malloc_c){};
	new->point = mal_p;
	save_type(&head, new, flag);
	return (head);
}

void	clear_point(t_malloc_c *malloc_h)
{
	t_malloc_c	*tmp;

	while (malloc_h)
	{
		tmp = malloc_h->next;
		free(malloc_h->point);
		free(malloc_h);
		malloc_h = tmp;
	}
}
