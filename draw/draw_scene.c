/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:03:12 by utygett           #+#    #+#             */
/*   Updated: 2022/04/03 16:07:40 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	aim_paint(t_data_mlx *data, int tar, int other, int side)
{
	int	aim_size;
	int	aim_w;

	aim_size = data->aim_size;
	while (aim_size--)
	{
		if (tar > (side / 2 + data->aim_size / 2) - data->aim_size / 3 || \
			tar < (side / 2 + data->aim_size / 2) - data->aim_size + \
			data->aim_size / 3)
		{
			aim_w = AIM_WIDTH;
			while (aim_w-- != -AIM_WIDTH)
			{
				if (side == WIDTH)
					my_mlx_pixel_put(data, tar, other / 2 - aim_w, GREEN_COL);
				else if (side == HEIGHT)
					my_mlx_pixel_put(data, other / 2 - aim_w, tar, GREEN_COL);
			}
		}
		tar--;
	}
}

void	draw_aim(t_data_mlx *data)
{
	if (data->keycode[SHIFT_KEY] == PRESS && (data->keycode[W_KEY] == PRESS || \
		data->keycode[S_KEY] == PRESS))
		data->aim_size = AIM_SIZE + 10;
	else
		data->aim_size = AIM_SIZE;
	if (data->keycode[W_KEY] == PRESS || data->keycode[S_KEY] == PRESS)
		data->aim_size += 10;
	aim_paint(data, HEIGHT / 2 + data->aim_size / 2, WIDTH, HEIGHT);
	aim_paint(data, WIDTH / 2 + data->aim_size / 2, HEIGHT, WIDTH);
}

void	put_weapon_image(t_data_mlx *data)
{
	static int	frame;
	int			a;

	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS || frame > 0)
	{
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			data->mouse_code[MOUSE_LEFT_KEY] = UNPRESS;
		frame += 5;
		if (frame > 24)
			frame = 0;
	}
	a = frame % 25;
	mlx_put_image_to_window(data->mlx, data->mlx_win, \
		data->am_s->weapon_textures->img, (WIDTH - \
		data->am_s->weapon_textures->img_w + a) - WIDTH / 11, \
		(HEIGHT - data->am_s->weapon_textures->img_h + a));
}

/* ground and sky */
void	draw_fvp(t_data_mlx *data)
{
	int	x;
	int	y;

	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	y = -1;
	while (++y < HEIGHT)
	{	
		x = -1;
		while (++x < WIDTH)
		{
			if (y < HEIGHT / 2 + data->map->cam.vertilcal_pos)
				my_mlx_pixel_put(data, x, y, data->map->sky_color);
			else
				my_mlx_pixel_put(data, x, y, data->map->floor_color);
		}
	}
	ray_play(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}
