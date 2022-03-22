/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:03:12 by utygett           #+#    #+#             */
/*   Updated: 2022/03/22 18:00:56 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	draw_aim(t_data_mlx *data)
{
	int x;
	int y;
	int aim_size;
	int	aim_width;

	if(data->keycode[SHIFT_KEY] == PRESS && (data->keycode[W_KEY] == PRESS || data->keycode[S_KEY] == PRESS))
		data->aim_size = AIM_SIZE + 10;
	else
		data->aim_size = AIM_SIZE;
	if(data->keycode[W_KEY] == PRESS || data->keycode[S_KEY] == PRESS)
		data->aim_size += 10;
	aim_size = data->aim_size;
	x = WIDTH / 2;
	y = HEIGHT / 2 + data->aim_size / 2;
	while(aim_size--)
	{
		if(y > (HEIGHT / 2 + data->aim_size / 2) - data->aim_size / 3 || y < (HEIGHT / 2 + data->aim_size / 2) - data->aim_size + data->aim_size / 3)
		{
			aim_width = AIM_WIDTH;
			while (aim_width-- != -AIM_WIDTH)
				my_mlx_pixel_put(data, x - aim_width, y, GREEN_COL);
		}
		y--;
	}
	aim_size = data->aim_size;
	x = WIDTH / 2 + data->aim_size / 2;
	y = HEIGHT / 2;
	while(aim_size--)
	{
		if(x > (WIDTH / 2 + data->aim_size / 2) - data->aim_size / 3 || x < (WIDTH / 2 + data->aim_size / 2) - data->aim_size + data->aim_size / 3)
		{
			aim_width = AIM_WIDTH;
			while (aim_width-- != -AIM_WIDTH)
				my_mlx_pixel_put(data, x, y - aim_width, GREEN_COL);
		}
		x--;
	}
}

void	put_weapon_image(t_data_mlx *data)
{
	static int	frame;
	int	a;
	// if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
	if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS || frame > 0)
	{
		if (data->mouse_code[MOUSE_LEFT_KEY] == PRESS)
			data->mouse_code[MOUSE_LEFT_KEY] = UNPRESS;
		frame += 5;
		if (frame > 24)
			frame = 0;
	}
	a = frame % 25;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->weapon.img, (WIDTH / 2 + WIDTH / 20) + a, (HEIGHT - data->weapon.img_h) + a);
}

void	draw_fvp(t_data_mlx *data)
{
	int	i;
	int x;
	int y;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	y = 0;
	// ground and sky
	while (y < HEIGHT)
	{	
		x = 0;
		while (x < WIDTH)
		{
			if(y < HEIGHT / 2 + data->map->cam.vertilcal_pos)
				my_mlx_pixel_put(data ,x, y, SKY_COL);
			else
				my_mlx_pixel_put(data, x, y, GROUND_COL);
			x++;
		}
		y++;
	}
	ray_play(data, 1);
	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}
