/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:37:15 by utygett           #+#    #+#             */
/*   Updated: 2022/04/02 21:33:26 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	line_math_minimap(t_data_mlx *data, float rad)
{
	float	c;
	float	ang;
	float	ray_x;
	float	ray_y;

	ang = data->map->play.a + rad;
	c = 0;
	while (c < MMTEXSIZE / 10)
	{
		ray_x = data->map->play.x + c * cos(ang);
		ray_y = data->map->play.y + c * sin(ang);
		if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0'
			|| data->map->mapa[(int)ray_y][(int)ray_x].door == 1)
			break ;
		ray_x *= MMTEXSIZE;
		ray_y *= MMTEXSIZE;
		c = c + 0.1f;
		pixel_put_map_move(ray_x, ray_y, data, PLAYERCOL);
	}
}

static void	draw_square_move(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + MMTEXSIZE)
	{
		j = 0;
		while (y + j < y + MMTEXSIZE)
		{	
			pixel_put_map_move(x + i, y + j, data, color);
			j++;
		}
		i++;
	}
}

static void	draw_field_move(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square_move(y * MMTEXSIZE, x * MMTEXSIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square_move(y * MMTEXSIZE, x * MMTEXSIZE, data, FLOORCOL);
	if (data->map->mapa[x][y].door == 1)
		draw_square_move(y * MMTEXSIZE, x * MMTEXSIZE, data, BLUE_COL);
}

void	draw_map_with_move(t_data_mlx *data)
{
	int		i;
	int		j;
	float	a;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			draw_field_move(i, j, data);
			j++;
		}
		i++;
	}
	a = MMANG_START;
	while (a < MMFOV)
	{
		line_math_minimap(data, a);
		a = a + MMANG_STEP;
	}
	draw_board(data);
}
