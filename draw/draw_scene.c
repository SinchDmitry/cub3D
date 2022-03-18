/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:03:12 by utygett           #+#    #+#             */
/*   Updated: 2022/03/18 15:34:10 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	step_counter_texture(float step, float value)
{
	int				i;
	float			step_buf;
	int				step_div;
	static float	old_value;
	static int		res;

	if (res * step < value && (res + 1) * step > value)
		return (res);
	step_div = 128;
	step_buf = step + 0.1f;
	i = 0;
	while (step <= value && step_div > 1)
	{
		while (step <= value)
		{
			step += step_buf * step_div;
			i = i + step_div;
		}
		step -= step_buf * step_div;
		i = i - step_div;
		step_div /= 2;
	}
	step += step_buf * step_div;
	i = i + step_div;
	if (i > 256)
		printf("SOMETHING WRONG\n"); // dont forget erase
	old_value = value;
	res = i;
	return (i);
}

void	draw_ray_cast(t_data_mlx *data, float x, float h, int w_pix)
{
	float	i;
	int		j;

	j = 0;
	i = 0 - (h / 2);
	while(i < -HEIGHT / 2)
	{
		// printf("I : %f\n", i);
		i++;
	}
	while (i < h / 2)
	{
		my_mlx_pixel_put(data, x, HEIGHT / 2 + i, my_mlx_get_pixel(data, w_pix, step_counter_texture(h / 256, h / 2 + i), 1));
		++i;
		if	(i > HEIGHT / 2)
			break;
	}
}

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

void	laser_width(t_data_mlx *data ,t_vls *bullet, int width_step)
{
	bullet->x1 = 40 + (WIDTH / 2 + WIDTH / 20) + width_step;
	bullet->y1 = 40 + (HEIGHT - data->weapon.img_h);
	bullet->x2 = WIDTH / 2 + width_step;
	bullet->y2 = HEIGHT / 2;
}

void	attack_weapon(t_data_mlx *data)
{
	t_vls	bullet;
	int		i;
	
	i = LASER_WIDTH;
	while (i >= 0)
	{
		laser_width(data, &bullet, i--);
		draw_line(data, bullet, RED_COL);
		printf ("x : %d < %d < %d \n", data->am_s->dr_st_x, WIDTH / 2, data->am_s->dr_f_x);
		printf ("y : %d < %d < %d \n", data->am_s->dr_st_y, HEIGHT / 2, data->am_s->dr_f_y);
		// if (WIDTH / 2 > data->am_s->dr_st_x && WIDTH / 2 < data->am_s->dr_f_x)
		// 	if (HEIGHT / 2 > data->am_s->dr_st_y && HEIGHT / 2 < data->am_s->dr_f_y)
				
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
			if(y < HEIGHT / 2 + data->map->camera.vertilcal_pos)
				my_mlx_pixel_put(data ,x, y, SKY_COL);
			else
				my_mlx_pixel_put(data, x, y, GROUND_COL);
			x++;
		}
		y++;
	}
	ray_player(data, 1);
	
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}
