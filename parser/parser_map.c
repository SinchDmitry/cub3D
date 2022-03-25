/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/25 20:25:28 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* needed? 
map->cam.pl_x = 0;
map->cam.pl_y = 0;
map->play.dir_x = 0;
map->play.dir_y = 0;
map->play.a = 0; */
static void	select_dir(t_info *map, char ch)
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

static int	ft_iscompas(t_info *map, char ch, int *first_in)
{
	if (ch == 'S' || ch == 'N' || ch == 'W' || ch == 'E')
	{
		if (*first_in)
			error_end(2);
		select_dir(map, ch);
		*first_in += 1;
		return (1);
	}
	else
		return (0);
}

static void	neighbor(t_info *map, int i, int j)
{
	if (i > 0)
		if (map->mapa[i - 1][j].sym == '0')
			error_end(2);
	if (i < map->max_i - 1)
		if (map->mapa[i + 1][j].sym == '0')
			error_end(2);
	if (j > 0)
		if (map->mapa[i][j - 1].sym == '0')
			error_end(2);
	if (j < map->max_j - 1)
		if (map->mapa[i][j + 1].sym == '0')
			error_end(2);
}

static void	map_check(t_info *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->max_i)
	{
		j = -1;
		while (++j < map->max_j)
		{
			if (map->mapa[i][j].sym == 'e')
				neighbor(map, i, j);
			else if (((!i || i == (map->max_i - 1)) && \
				map->mapa[i][j].sym == '0') || ((!j || j == (map->max_j - 1)) \
				&& map->mapa[i][j].sym == '0'))
				error_end(2);
		}
	}
}

void	map_create(t_info *map, char **map_str)
{
	int	f;

	map->max_i = -1;
	f = 0;
	while (map_str[++map->max_i])
	{
		map->max_j = -1;
		while (map_str[map->max_i][++map->max_j])
		{
			if (space(map_str[map->max_i][map->max_j]))
				map->mapa[map->max_i][map->max_j].sym = 'e';
			else if (ft_iscompas(map, map_str[map->max_i][map->max_j], &f))
			{
					map->play.dir = map_str[map->max_i][map->max_j];
					map->play.x = (float)map->max_j;
					map->play.y = (float)map->max_i;
					map->mapa[map->max_i][map->max_j].sym = '0';
			}
			else
				map->mapa[map->max_i][map->max_j].sym = \
				map_str[map->max_i][map->max_j];
		}
	}
	map_check(map);
}
