/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/04/03 17:40:36 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

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

int	end_program(int keycode, t_data_mlx *data)
{
	(void) keycode;
	(void) data;
	error_end(0);
	return (0);
}

void	init_map_texture_size(t_data_mlx *data)
{
	int	tmp;
	int	i;

	i = 0;
	tmp = data->map->width;
	if (data->map->width < data->map->height)
		tmp = data->map->height;
	while (++i * tmp < HEIGHT)
		data->map->texture_size = i;
}

int	draw(t_data_mlx	*data)
{
	int	i;

	i = 0;
	data->door_str = ft_calloc_error_end(WIDTH * sizeof(t_door_st), 1, P_FRONT);
	while (i < MAX_KEYS_NUM)
		data->keycode[i++] = UNPRESS;
	data->mouse_x = WIDTH / 2;
	data->mouse_y = HEIGHT / 2;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx_mouse_move(data->mlx_win, WIDTH / 2, HEIGHT / 2);
	data->wall_img = ft_calloc_error_end(sizeof(t_wall_tex), 1, P_FRONT);
	init_map_texture_size(data);
	init_sprites(data);
	check_obj_in_map(data, data->am_s->spr_img);
	check_obj_in_map(data, data->am_s->comp_img);
	mlx_hook(data->mlx_win, 2, 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 0, &key_unpress, data);
	mlx_hook(data->mlx_win, 17, 0, &end_program, data);
	mlx_mouse_hook(data->mlx_win, &ft_mouse, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return (0);
}
