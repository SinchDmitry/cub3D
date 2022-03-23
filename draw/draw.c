/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/23 13:13:31 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	my_mlx_get_pixel(t_tex costume, int x, int y)
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

int	check_move(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->play.y] \
		[(int)data->map->play.x].sym == '1')
		return (1);
	else
		return (0);
}

int	render_next_frame(t_data_mlx *data)
{
	int			img_h;
	int			img_w;
	static int	i_space;

	if (data->map->play.f_map)
	{
		draw_fvp(data);
		draw_objects(data);
		if (data->map->play.f_minimap)
			draw_minimap(data);
	}
	if (!data->map->play.f_map)
	{	
		++i_space;
		if (i_space > 39)
			i_space = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i_space], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, \
			WIDTH / 2 - data->map->width * TEXSIZE / 2, \
			HEIGHT / 2 - data->map->height * TEXSIZE / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
	mouse_move(data);
	key_h(data);
	mlx_mouse_hide();
	return (0);
}

int	key_press(int keycode, t_data_mlx *data)
{
	map_exit_case(keycode, data);
	if (keycode >= 0 && keycode < MAX_KEYS_NUM)
		data->keycode[keycode] = PRESS;
	return (0);
}

int	key_unpress(int keycode, t_data_mlx *data)
{
	if (keycode >= 0 && keycode < MAX_KEYS_NUM)
		data->keycode[keycode] = UNPRESS;
	return (0);
}

int	draw(t_info *map)
{
	t_data_mlx	data;
	int i;

	i = 0;
	map->play.f_map = 0;
	map->play.f_minimap = 0;
	data.map = map;
	data.map->cam.vertilcal_pos = 0;
	while(i < MAX_KEYS_NUM)
		data.keycode[i++] = UNPRESS; //init unpress keys
	data.mouse_x = WIDTH / 2;
	data.mouse_y = HEIGHT / 2;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_mouse_move(data.mlx_win, WIDTH / 2, HEIGHT / 2);
	init_images(&data);
	// init_sprite_data(&data);
	mlx_hook(data.mlx_win, 2, 0, &key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, &key_unpress, &data);
	mlx_mouse_hook(data.mlx_win, &ft_mouse, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_loop(data.mlx);
	return (0);
}
