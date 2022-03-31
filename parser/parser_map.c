/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/31 13:52:42 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* needed? 
map->cam.pl_x = 0;
map->cam.pl_y = 0;
map->play.dir_x = 0;
map->play.dir_y = 0;
map->play.a = 0; */
static void	select_dir(t_map_info *map, char ch)
{
	if (ch == 'N')
	{
		map->cam.pl_x = tan(FOV / 2);
		map->play.dir_y = tan(-FOV / 2);
		map->play.a = 4.7124f;
	}
	else if (ch == 'S')
	{
		map->cam.pl_x = tan(-FOV / 2);
		map->play.dir_y = tan(FOV / 2);
		map->play.a = 1.5708f;
	}
	else if (ch == 'E')
	{
		map->cam.pl_y = tan(FOV / 2);
		map->play.dir_x = tan(FOV / 2);
	}
	else if (ch == 'W')
	{
		map->cam.pl_y = tan(-FOV / 2);
		map->play.dir_x = tan(-FOV / 2);
		map->play.a = 3.1415f;
	}
}

static void	map_check(t_map_info *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->mapa[i][j].sym == 'e')
				neighbor(map, i, j);
			else if (((!i || i == (map->width - 1)) && \
				map->mapa[i][j].sym == '0') || ((!j || j == (map->width - 1)) \
				&& map->mapa[i][j].sym == '0'))
				error_end(2);
		}
	}
}

static int	slot_check(t_data_mlx *data, char **map_str, int i, int j)
{
	int	f;

	f = 0;
	if (space(map_str[i][j]))
		data->map->mapa[i][j].sym = 'e';
	if (map_str[i][j] == '2' && BONUS_MODE)
	{
		data->map->mapa[i][j].sym = '0';
		data->map->mapa[i][j].door = 1;
	}
	else if (ft_iscompas(data->map, map_str[i][j], &f))
	{
		data->map->play.dir = map_str[i][j];
		data->map->play.x = (float)j;
		data->map->play.y = (float)i;
		data->map->mapa[i][j].sym = '0';
	}
	else if (map_str[i][j] == '0' || map_str[i][j] == '1')
		data->map->mapa[i][j].sym = map_str[i][j];
	else
		error_end(1);
	return (f);
}

/* f - player on map flag */
void	map_create(t_data_mlx *data, char **map_str)
{
	int	i;
	int	j;
	int	f;

	i = -1;
	f = 0;
	while (map_str[++i])
	{
		j = -1;
		while (map_str[i][++j])
			f += slot_check(data, map_str, i, j);
	}
	if (f != 1)
		error_end(1);
	map_check(data->map);
}

// void	map_create(t_data_mlx *data, char **map_str, int f)
// {
// 	int	j;

// 	data->map->max_i = -1;
// 	data->map->max_j = -1;
// 	while (map_str[++data->map->max_i])
// 	{
// 		j = -1;
// 		while (map_str[data->map->max_i][++j])
// 		{
// 			if (space(map_str[data->map->max_i][j]))
// 				data->map->mapa[data->map->max_i][j].sym = 'e';
// 			else if (ft_iscompas(data->map, map_str[data->map->max_i][j], &f))
// 			{
// 				data->map->play.dir = map_str[data->map->max_i][j];
// 				data->map->play.x = (float)j;
// 				data->map->play.y = (float)data->map->max_i;
// 				data->map->mapa[data->map->max_i][j].sym = '0';
// 			}
// 			else
// 				data->map->mapa[data->map->max_i][j].sym = 
// 					map_str[data->map->max_i][j];
// 		}
// 		if (j > data->map->max_j)
// 			data->map->max_j = j;
// 	}
// 	map_check(data->map);
// }
