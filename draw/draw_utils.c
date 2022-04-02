/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:44:09 by utygett           #+#    #+#             */
/*   Updated: 2022/04/02 21:33:26 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_invis_background(t_data_mlx *data, int height, int width)
{
	int	i;
	int	j;

	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			my_mlx_pixel_put(data, i, j, INVISIBLE_COL);
	}
}

void	pixel_put_map_move(int x, int y, t_data_mlx *data, int color)
{
	float	x1;
	float	y1;
	float	h;
	float	w;

	x1 = x;
	y1 = y;
	h = ((data->map->play.x) * MMTEXSIZE);
	w = ((data->map->play.y) * MMTEXSIZE);
	x = ((x1 - h) * sin(data->map->play.a + ROTATE_MOV) - (y1 - w) * \
		cos(data->map->play.a + ROTATE_MOV));
	y = ((x1 - h) * cos(data->map->play.a + ROTATE_MOV) + (y1 - w) * \
		sin(data->map->play.a + ROTATE_MOV));
	if (x + MOVEX < MINIMAPHEIGHT && y + MOVEY < MINIMAPWIDTH && \
		x + MOVEX > 0 && y + MOVEY > 0)
		my_mlx_pixel_put(data, x + MOVEX, y + MOVEY, color);
}

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
