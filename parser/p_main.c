/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:54:20 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/14 22:11:09 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	init_map_data(t_info **map, int fd)
{
	*map = malloc(sizeof(t_info));
	if (!map)
		error_end(3);
	save_point(*map, P_BACK);
	**map = (t_info){};
	(*map)->texture = malloc(sizeof(t_texture));
	if (!(*map)->texture)
		error_end(3);
	save_point((*map)->texture, P_FRONT);
	(*map)->floor = malloc(sizeof(t_rgb));
	if (!(*map)->floor)
		error_end(3);
	save_point((*map)->floor, P_FRONT);
	(*map)->sky = malloc(sizeof(t_rgb));
	if (!(*map)->sky)
		error_end(3);
	save_point((*map)->sky, P_FRONT);
	(*map)->fd = fd;
}

t_info	*parser(int argc, char **argv, int fd)
{
	t_info	*map;
	char	**map_str;

	if (argc != 2 || ft_strcmp_rev(argv[1], ".cub") || fd < 2)
		error_end(1);
	init_map_data(&map, fd);
	printf("here %d\n", map->fd);
	map_str = get_line_file(map->fd);
	if (!map_str)
		error_end(3);
	save_point(map_str, 2);
	param_info(map, map_str);
	printf ("h : %d\nw : %d\n", map->height, map->width);
	return (map);
}
