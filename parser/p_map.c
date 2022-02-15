/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/15 17:03:57 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static void	map_create(t_info *map, char **map_str)
{
	int	i;
	int	j;

	i = -1;
	while (map_str[++i])
	{
		j = -1;
		while (map_str[i][++j])
		{
			if (space(map_str[i][j]))
				map->mapa[i][j].sym = 'e';
			else
				map->mapa[i][j].sym = map_str[i][j];
			printf ("%c ", map->mapa[i][j].sym);
		}
		printf ("\n");
	}
}

void	map_struct(t_info *map, char **map_str)
{
	int	i;

	i = -1;
	map->mapa = malloc(sizeof(t_data *) * (map->height + 1));
	if (!map->mapa)
		error_end(3);
	save_point(map->mapa, P_FRONT);
	while (++i < map->height)
	{
		map->mapa[i] = malloc(sizeof(t_data) * (map->width));
		if (!map->mapa[i])
			error_end(3);
		save_point(map->mapa[i], P_FRONT);
	}
	map_create(map, map_str);
}
