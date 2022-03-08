/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:50:19 by utygett           #+#    #+#             */
/*   Updated: 2022/03/08 19:27:30 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	pixel_put_map_move(int x, int y, t_data_mlx *data, int color)
{
	float	x1;
	float	y1;
	float	h;
	float	w;

	x1 = x;
	y1 = y;
	h = ((data->map->player.x) * MMTEXSIZE);
	w = ((data->map->player.y) * MMTEXSIZE);
	x = ((x1 - h) * sin(data->map->player.a + ROTATE_MOV) - (y1 - w) * \
		cos(data->map->player.a + ROTATE_MOV));
	y = ((x1 - h) * cos(data->map->player.a + ROTATE_MOV) + (y1 - w) * \
		sin(data->map->player.a + ROTATE_MOV));
	if (x + MOVEX < MINIMAPHEIGHT && y + MOVEY < MINIMAPWIDTH && \
		x + MOVEX > 0 && y + MOVEY > 0)
		my_mlx_pixel_put(data, x + MOVEX, y + MOVEY, color);
}

void	draw_square_move(int x, int y, t_data_mlx *data, int color)
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

void	draw_invis_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + MMTEXSIZE)
	{
		j = 0;
		while (y + j < y + MMTEXSIZE)
		{	
			my_mlx_pixel_put(data, y, x, color);
			j++;
		}
		i++;
	}
}

void	draw_field_move(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square_move(y * MMTEXSIZE, x * MMTEXSIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square_move(y * MMTEXSIZE, x * MMTEXSIZE, data, FLOORCOL);
}

void	line_math_minimap(t_data_mlx *data, float rad)
{
	float	c;
	float	ang;
	float	ray_x;
	float	ray_y;

	ang = data->map->player.a + rad;
	c = 0;
	while (c < 2)
	{
		ray_x = data->map->player.x + c * cos(ang);
		ray_y = data->map->player.y + c * sin(ang);
		if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
			break ;
		ray_x *= MMTEXSIZE;
		ray_y *= MMTEXSIZE;
		c = c + 0.1f;
		pixel_put_map_move(ray_x, ray_y, data, PLAYERCOL);
	}
}

void	draw_invis_background(t_data_mlx *data, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{	
			my_mlx_pixel_put(data, i , j , INVISIBLE_COL);
			j++;
		}
		i++;
	}
}

int	in_circle(float x, float y, int r)
{
	float	distance;

	distance = sqrtf(powf(x - MOVEX, 2.0f) + powf(y -  MOVEY, 2.0f));
	if (distance <= r)
	{
		if ((r - distance) < 1.0f)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_board(t_data_mlx *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAPHEIGHT)
	{
		j = 0;
		while (j < MINIMAPWIDTH)
		{	
			if (!in_circle(j, i, 100))
				my_mlx_pixel_put(data, i , j , INVISIBLE_COL);
			if (in_circle(j, i, 100) == 2)
				my_mlx_pixel_put(data, i , j , WHITE_COL);
			if (in_circle(j, i, MMTEXSIZE / 4) == 1)
				my_mlx_pixel_put(data, i , j , WHITE_COL);
			j++;
		}
		i++;
	}
}

void	draw_map_with_move(t_data_mlx *data)
{
	int	i;
	int	j;
	float	a;

	i = 0;
	draw_invis_background(data, MINIMAPHEIGHT, MINIMAPWIDTH);
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
