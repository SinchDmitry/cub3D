/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 22:21:04 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/14 22:49:10 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	map_struct(t_info *map, char **map_str)
{
	int	i;
	int	j;
	
	i = -1;
	map->mapa = malloc (sizeof(t_data *) * map->height);
	if (!map->mapa)
		error_end(3);
	save_point(map->mapa, P_FRONT);
	while (map->mapa[++i])
	{
		map->mapa[i] = malloc (sizeof(t_data) * map->width);
		if (!map->mapa)
			error_end(3);
		save_point(map->mapa[i], P_FRONT);
	}
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
