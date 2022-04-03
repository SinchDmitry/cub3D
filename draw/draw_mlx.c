/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:33:52 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/03 17:49:33 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

unsigned int	my_mlx_get_pixel(t_cost_tex costume, int x, int y)
{	
	return (*(unsigned int *)(costume.addr + \
		(x * costume.bits_per_pixel / 8 + y * costume.line_length)));
}

void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

static void	render_img(t_data_mlx *data)
{
	static int	i_space;

	if (data->map->play.f_map)
	{	
		++i_space;
		if (i_space > 39)
			i_space = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->am_s->space_textures[i_space].img, 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, \
			WIDTH / 2 - data->map->width * data->map->texture_size / 2, \
			HEIGHT / 2 - data->map->height * data->map->texture_size / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
}

void	check_mouse(t_data_mlx *data)
{
	if (data->mouse_f)
		mouse_move(data);
	if (data->keycode[18])
	{
		mlx_mouse_hide();
		data->mouse_f = 1;
	}
	if (data->keycode[19])
	{
		data->mouse_f = 0;
		mlx_mouse_show();
	}
}

int	render_next_frame(t_data_mlx *data)
{
	data->frame_num++;
	check_sprite_position(data);
	check_door_state(data, data->map->mapa);
	draw_fvp(data);
	draw_objects(data);
	if (data->map->play.f_minimap)
		draw_minimap(data);
	render_img(data);
	check_mouse(data);
	key_h(data);
	return (0);
}
