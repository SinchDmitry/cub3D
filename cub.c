/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:13:00 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/15 17:19:02 by aarchiba         ###   ########.fr       */
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
	error_end(4);
	return (0);
}
