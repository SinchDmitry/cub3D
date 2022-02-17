/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:13:00 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/17 14:52:58 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_addr(void)
{
	t_malloc_c	*tmp;
	int			i;

	tmp = save_point(NULL, 0);
	i = 0;
	printf ("\n*******************************\n");
	while (tmp)
	{
		printf("%2d : %p\n", i++, tmp->point);
		tmp = tmp->next;
	}
	printf ("\n*******************************\n");
}

int	main(int argc, char **argv)
{
	char	**res;
	t_info	*map;
	int		fd;
	int		i;

	res = NULL;
	i = -1;
	fd = open(argv[1], O_RDONLY);
	map = parser(argc, argv, fd);
	save_point(map, P_BACK);
	draw(map);
	error_end(4);
	return (0);
}
