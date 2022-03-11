/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:03:12 by utygett           #+#    #+#             */
/*   Updated: 2022/03/11 21:34:42 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	step_counter_texture(float step, float value)
{
	int		i;
	float	step_buf;
	int		step_div;
	static float old_value;
	static int res;

	if(res * step < value && (res + 1) * step > value)
		return(res);
	step_div = 128;
	step_buf = step + 0.1f;
	i = 0; 
	while (step <= value && step_div > 1)
	{
		while (step <= value)
		{
			// printf("step : %f buf : %f value : %f\n", step, step_buf, value);
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
	// if (value > 256)
		// printf("i : %d\n", i);
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

// void	ray_analys(t_data_mlx *data, int c, int x)
// {
// 	float	y;

// 	y = HEIGHT / (data->sector[c]);
// 	if (data->sector[c] < VIEW_RANGE)
// 	{
// 		// printf ("%3d : %f\n", c, data->sector[c]);
// 		draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, 0));
// 		// if (data->sector_y[c] - (int)data->sector_y[c] <= 0.0001f && \
// 		// 	data->sector_x[c] - (int)data->sector_x[c] <= 1)
// 		// 	draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
// 		// 		data->sector_x[c] - (int)data->sector_x[c]));
// 		// 	// printf("WHITE");
// 		// else if (data->sector_y[c] - (int)data->sector_y[c] <= 1 && \
// 		// 	data->sector_x[c] - (int)data->sector_x[c] < 0.0001f)
// 		// 	draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
// 		// 		data->sector_y[c] - (int)data->sector_y[c]));
// 		// 	// printf("RED  ");
// 		// else if (data->sector_y[c] - (int)data->sector_y[c] >= 0.9999f \
// 		// 	&& data->sector_x[c] - (int)data->sector_x[c] >= 0.0001f)
// 		// 	draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
// 		// 		data->sector_x[c] - (int)data->sector_x[c]));
// 		// 	// printf("GREEN");
// 		// else
// 		// 	draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
// 		// 		data->sector_y[c] - (int)data->sector_y[c]));
// 		// 	// printf("BLUE ");
// 	}
// }

void	draw_fvp(t_data_mlx *data)
{
	int	i;
	
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	ray_player(data, 1);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}
