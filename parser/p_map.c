/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/21 20:52:29 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	select_dir(t_info *map, char ch)
{
	if (ch == 'N')
	{
		map->cam.pl_x = tan(FOV / 2);
		map->cam.pl_y = 0;
		map->play.dir_x = 0;
		map->play.dir_y = tan(-FOV / 2);
		map->play.a = 4.7124f;
	}
	else if (ch == 'S')
	{
		map->cam.pl_x = tan(-FOV / 2);
		map->cam.pl_y = 0;
		map->play.dir_x = 0;
		map->play.dir_y = tan(FOV / 2);
		map->play.a = 1.5708f;
	}
	else if (ch == 'E')
	{
		map->cam.pl_x = 0;
		map->cam.pl_y = tan(FOV / 2);
		map->play.dir_x = tan(FOV / 2);
		map->play.dir_y = 0;
		map->play.a = 0;
	}
	else if (ch == 'W')
	{
		map->cam.pl_x = 0;
		map->cam.pl_y = tan(-FOV / 2);
		map->play.dir_x = tan(-FOV / 2);
		map->play.dir_y = 0;
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

void	map_info(t_info *map, char **map_str)
{
	int		i;
	int		j;

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
	map_struct(map, map_str + (param_map(map, map_str)));
}

static void map_check(t_info *map, int max_i, int max_j)
{
	int	i;
	int	j;

	i = -1;
	while (++i < max_i)
	{
		j = -1;
		while (++j < max_j)
		{
			if (map->mapa[i][j].sym == 'e')
			{
				if (i > 0)
					if (map->mapa[i - 1][j].sym == '0')
						error_end(2);
				if (i < max_i - 1)
					if (map->mapa[i + 1][j].sym == '0')
						error_end(2);
				if (j > 0)
					if (map->mapa[i][j - 1].sym == '0')
						error_end(2);
				if (j < max_j - 1)
					if (map->mapa[i][j + 1].sym == '0')
						error_end(2);
			}
			else if (((!i || i == (max_i - 1)) && map->mapa[i][j].sym == '0') \
				|| ((!j || j == (max_j - 1)) && map->mapa[i][j].sym == '0'))
				error_end(2);
		}
	}
}

static void	map_create(t_info *map, char **map_str)
{
	int	i;
	int	j;
	int f;

	i = -1;
	f = 0;
	while (map_str[++i])
	{
		j = -1;
		while (map_str[i][++j])
		{
			if (space(map_str[i][j]))
				map->mapa[i][j].sym = 'e';
			else if (ft_iscompas(map, map_str[i][j], &f))
			{
					map->play.dir = map_str[i][j];
					map->play.x = (float)j;
					map->play.y = (float)i;
					map->mapa[i][j].sym = '0';
			}
			else
				map->mapa[i][j].sym = map_str[i][j];
		}
	}
	map_check(map, i, j);
}

void	map_struct(t_info *map, char **map_str)
{
	int	i;

	i = -1;
	map->mapa = malloc(sizeof(t_slot *) * (map->height + 1));
	if (!map->mapa)
		error_end(3);
	save_point(map->mapa, P_FRONT);
	while (++i < map->height)
	{
		map->mapa[i] = malloc(sizeof(t_slot) * (map->width));
		if (!map->mapa[i])
			error_end(3);
		save_point(map->mapa[i], P_FRONT);
	}
	map_create(map, map_str);
}
