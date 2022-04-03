/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 18:28:08 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	map_check(t_map_info *map)
{
	int	i;
	int	j;
	int	f;

	i = -1;
	while (++i < map->height)
	{
		f = 0;
		j = -1;
		while (++j < map->width)
		{
			if (map->mapa[i][j].sym == '1')
				f = 1;
			if (map->mapa[i][j].sym == 'e')
				neighbor(map, i, j);
			else if (((!i || i == (map->height - 1)) && \
				map->mapa[i][j].sym == '0') || ((!j || j == (map->width - 1)) \
				&& map->mapa[i][j].sym == '0'))
				error_end(2);
		}
		if (!f)
			error_end(1);
	}
}

static int	slot_check(t_data_mlx *data, char **map_str, int i, int j)
{
	int	f;

	f = 0;
	if (space(map_str[i][j]))
		data->map->mapa[i][j].sym = 'e';
	else if (ft_iscompas(data->map, map_str[i][j], &f))
	{
		data->map->play.dir = map_str[i][j];
		data->map->play.x = (float)j + 0.5;
		data->map->play.y = (float)i + 0.5;
		data->map->mapa[i][j].sym = '0';
	}
	else if (map_str[i][j] == '0' || map_str[i][j] == '1')
		data->map->mapa[i][j].sym = map_str[i][j];
	else
		error_end(1);
	return (f);
}

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
		while (j < data->map->width)
			data->map->mapa[i][j++].sym = 'e';
	}
	if (f != 1)
		error_end(1);
	map_check(data->map);
}
