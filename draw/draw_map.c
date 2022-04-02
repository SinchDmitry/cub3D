/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:04:49 by utygett           #+#    #+#             */
/*   Updated: 2022/04/02 13:48:00 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// int	**init_play_arrow()
// {
// 	int	i;
// 	int	**img;

// 	i = -1;
// 	img = malloc(sizeof(int *) * 10);
// 	if (!img)
// 		error_end(3);
// 	save_point(img, P_BACK);
// 	while (++i < 10)
// 	{
// 		img[i] = malloc
// 	}
// }
void	draw_play(t_play *play, t_data_mlx *data)
{
	float	x;
	float	y;
	float	point_x;
	float	point_y;
	int		play_draw[10][10] =
	{
	{1, 1, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 1, 1, 1, 0, 0, 1, 1, 1, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 0, 0, 0, 0}
	};

	play->x_textu = play->x * TEXSIZE;
	play->y_textu = play->y * TEXSIZE;
	x = play->x_textu;
	y = play->y_textu;
	while (x < play->x_textu + 10)
	{
		y = play->y_textu;
		while (y < play->y_textu + 10)
		{
			point_x = (x - play->x_textu - 5) * cos(data->map->play.a) - \
				(y - play->y_textu - 5) * sin(data->map->play.a);
			point_y = (x - play->x_textu - 5) * sin(data->map->play.a) + \
				(y - play->y_textu - 5) * cos(data->map->play.a);
			if (play_draw[(int)(x - play->x_textu)] \
				[(int)(y - play->y_textu)] == 1)
				my_mlx_pixel_put(data, point_x + play->x_textu, point_y + \
					play->y_textu, GREEN_COL);
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

void	draw_field(int x, int y, t_data_mlx *data)
{
	t_spr_tex	*tmp_img;
	if (data->map->mapa[x][y].sym == '1')
		draw_square(y * TEXSIZE, x * TEXSIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square(y * TEXSIZE, x * TEXSIZE, data, FLOORCOL);
	if (data->map->mapa[x][y].door == 1)
		draw_square(y * TEXSIZE, x * TEXSIZE, data, BLUE_COL);
	tmp_img = data->am_s->spr_img;
	while (tmp_img)
	{	
		draw_square((int)tmp_img->x * TEXSIZE, (int)tmp_img->y * TEXSIZE, data, RED_COL);
		tmp_img = tmp_img->next;
	}
}

void	draw_map(t_data_mlx *data)
{
	int		i;
	int		j;

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
	draw_play(&data->map->play, data);
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

void	draw_line(t_data_mlx *data, t_vls xyz, int color)
{
	t_line	line_w;

	init_list(&line_w, &xyz);
	while ((int)(xyz.x1 - xyz.x2) || (int)(xyz.y1 - xyz.y2))
	{
		my_mlx_pixel_put(data, xyz.x1, xyz.y1, color);
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
