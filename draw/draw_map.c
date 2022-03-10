/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:04:49 by utygett           #+#    #+#             */
/*   Updated: 2022/03/10 18:32:41 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_player(t_player *player, t_data_mlx *data)
{
	float	x;
	float	y;

	player->x_textu = player->x * TEXSIZE;
	player->y_textu = player->y * TEXSIZE;
	x = player->x_textu;
	y = player->y_textu;
	while (x < player->x_textu + (TEXSIZE / 2))
	{
		y = player->y_textu;
		while (y < player->y_textu + (TEXSIZE / 2))
		{
			my_mlx_pixel_put(data, x - (TEXSIZE / 4), \
				y - (TEXSIZE / 4), PLAYERCOL);
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
	while (x + i < x + TEXSIZE)
	{
		j = 0;
		while (y + j < y + TEXSIZE)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}	
}

// void	line_math(t_data_mlx *data, float rad)
// {
// 	float	c;
// 	float	ang;
// 	float	ray_x;
// 	float	ray_y;

// 	c = 0;
// 	ang = data->map->player.a + rad;
// 	while (c < 2)
// 	{
// 		ray_x = data->map->player.x + c * cos(ang);
// 		ray_y = data->map->player.y + c * sin(ang);
// 		if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
// 			break ;
// 		c += 0.01;
// 		ray_x *= TEXSIZE;
// 		ray_y *= TEXSIZE;
// 		my_mlx_pixel_put(data, ray_x, ray_y, PLAYERCOL);
// 	}
// }

void	draw_field(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square(y * TEXSIZE, x * TEXSIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square(y * TEXSIZE, x * TEXSIZE, data, FLOORCOL);
}

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
}

/**********************************************/

static void	init_list(t_line *line, t_vls *xyz)
{
	line->st_x1 = xyz->x1;
	line->st_x2 = xyz->x2;
	line->st_y1 = xyz->y1;
	line->st_y2 = xyz->y2;
	line->flag = 0;
	line->delta_x = fabsf(xyz->x2 - xyz->x1);
	line->tmp_delta = line->delta_x;
	line->delta_y = fabsf(xyz->y2 - xyz->y1);
	if (line->delta_x < line->delta_y)
	{
		line->tmp_delta = line->delta_y;
		line->flag = 1;
	}
	line->sign_x = -1;
	if (xyz->x1 < xyz->x2)
		line->sign_x = 1;
	line->sign_y = -1;
	if (xyz->y1 < xyz->y2)
		line->sign_y = 1;
	line->error = line->delta_x - line->delta_y;
}

void	draw_line(t_data_mlx *data, t_vls xyz)
{
	t_line	line_w;

	init_list(&line_w, &xyz);
	while ((int)(xyz.x1 - xyz.x2) || (int)(xyz.y1 - xyz.y2))
	{
		my_mlx_pixel_put(data, xyz.x1, xyz.y1, GREEN_COL);
		line_w.error2 = line_w.error * 2;
		if (line_w.error2 > -line_w.delta_y)
		{
			line_w.error -= line_w.delta_y;
			xyz.x1 += line_w.sign_x;
		}
		if (line_w.error2 < line_w.delta_x)
		{
			line_w.error += line_w.delta_x;
			xyz.y1 += line_w.sign_y;
		}
	}
}
