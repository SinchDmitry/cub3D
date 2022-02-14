/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 18:13:00 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/14 20:11:28 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	char	**res;
	int		fd;
	int		i;

	res = NULL;
	i = -1;
	fd = open(argv[1], O_RDONLY);
	parser(argc, argv, fd);
	return (0);
}
