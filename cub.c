/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:13:00 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 23:35:19 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	char		**res;
	t_data_mlx	data;
	int			fd;
	int			i;

	data = (t_data_mlx){};
	res = NULL;
	i = -1;
	fd = open(argv[1], O_RDONLY);
	parser(&data, argc, argv, fd);
	draw(&data);
	error_end(4);
	return (0);
}

/*
void	print_addr(void)
{
	t_malloc_c	*tmp;
	int			i;

	tmp = save_point(NULL, 0);
	i = 0;
	printf ("\n******************************\n");
	while (tmp)
	{
		printf("%2d : %p\n", i++, tmp->point);
		tmp = tmp->next;
	}
	printf ("\n******************************\n");
}
*/