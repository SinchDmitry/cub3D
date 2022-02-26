/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:04:49 by utygett           #+#    #+#             */
/*   Updated: 2022/02/26 13:52:59 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_player(t_player *player, t_data_mlx *data)
{
	float	x;
	float	y;

	player->x_textu = player->x * TEXTURESIZE;
	player->y_textu = player->y * TEXTURESIZE;
	x = player->x_textu;
	y = player->y_textu;
	while (x < player->x_textu + (TEXTURESIZE / 2))
	{
		y = player->y_textu;
		while (y < player->y_textu + (TEXTURESIZE / 2))
		{
			my_mlx_pixel_put(data, x - (TEXTURESIZE / 4), \
				y - (TEXTURESIZE / 4), PLAYERCOL);
			y++;
		}
		x++;
	}
}

void	draw_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + TEXTURESIZE)
	{
		j = 0;
		while (y + j < y + TEXTURESIZE)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}	
}

void	line_math(t_data_mlx *data, float rad)
{
	float	c;
	float	ang;
	float	ray_x;
	float	ray_y;

	c = 0;
	ang = data->map->player.a + rad;
	
		while (c < 2)
		{
			ray_x = data->map->player.x + c * cos(ang);
			ray_y = data->map->player.y + c * sin(ang);
			if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
				break ;
			c += 0.01;
			ray_x *= TEXTURESIZE;
			ray_y *= TEXTURESIZE;
			my_mlx_pixel_put(data, ray_x, ray_y, PLAYERCOL);
		}
}

void	draw_field(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, FLOORCOL);
}

// void draw_invis_background(t_data_mlx *data, int w, int h)
// {
// 	int	y;
// 	int	x;

// 	y = 0;
// 	while(y <= h)
// 	{
// 		x = 0;
// 		while (x <= w)
// 		{
// 			my_mlx_pixel_put(data, x, y, INVISIBLE_COL);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	draw_map(t_data_mlx *data)
{
	int		i;
	int		j;
	float	a;

	i = 0;
	draw_invis_background(data, WIDTH, HEIGHT);
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			draw_field(i, j, data);
			j++;
		}
		i++;
	}
	draw_player(&data->map->player, data);
	a = MMANG_START;
	while (a < MMFOV)
	{
		line_math(data, a);
		a = a + MMANG_STEP;
	}	
}