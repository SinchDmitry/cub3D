/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/13 20:56:38 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	param_info(t_info *map, char **map_str)
{
	int	i;
	int	j;

	while (map_str[map->height])
	{
		i = 0;
		j = -1;
		while (map_str[map->height][++j])
			i++;
		if (i > map->width)
			map->width = i;
		map->height++;
	}
}

// void	arg_init(t_info *map, char **map_str)
// {
// 	while (1)
// 	{
// 	}
// }

t_info	*parser(int argc, char **argv)
{
	t_info	*map;
	char	**map_str;

	*map = (t_info){};
	map->fd = open(argv[1], O_RDONLY);
	if (argc != 2 || ft_strcmp_rev(argv[1], ".cub") || map->fd < 2)
		error_end(1);
	map_str = get_line_file(map->fd);
	if (!map_str)
		error_end(3);
	save_point(map_str, 2);
	param_info(map, map_str);
	printf ("h : %d\nw : %d\n", map->height, map->width);
	return (map);
}

int	main(int argc, char **argv)
{
	char	**res;
	int		fd;
	int		i;

	res = NULL;
	i = -1;
	fd = open(argv[1], O_RDONLY);
	printf("fd : %d\n", fd);
	parser(argc, argv);
	return (0);
}
