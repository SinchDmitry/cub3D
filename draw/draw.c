/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/04/01 20:50:03 by utygett          ###   ########.fr       */
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

int	draw(t_data_mlx	*data)
{
	int			i;

	i = 0;
	data->door_struct = ft_calloc(WIDTH, sizeof(t_door_st));
	data->map->play.f_map = 0;
	data->map->play.f_minimap = 0;
	data->map->cam.vertilcal_pos = 0;
	data->map->mapa[12][5].door = 1; //del
	data->map->mapa[12][5].door_state = 0; //del
	data->map->mapa[12][8].door = 1; //del
	data->map->mapa[12][8].door_state = 0; //del
	while (i < MAX_KEYS_NUM)
		data->keycode[i++] = UNPRESS; //init unpress keys
	data->mouse_x = WIDTH / 2;
	data->mouse_y = HEIGHT / 2;
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_mouse_move(data->mlx_win, WIDTH / 2, HEIGHT / 2);
	init_images(data);
	mlx_hook(data->mlx_win, 2, 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 0, &key_unpress, data);
	mlx_mouse_hook(data->mlx_win, &ft_mouse, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
	return (0);
}
