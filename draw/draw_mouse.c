/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:39:35 by utygett           #+#    #+#             */
/*   Updated: 2022/04/01 22:34:15 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	ft_mouse(int keycode, int x, int y, t_data_mlx *data)
{	
	(void)x;
	(void)y;
	if (keycode == MOUSE_LEFT_KEY)
		data->mouse_code[keycode] = PRESS;
	return (0);
}

static void	mouse_on_screen(t_data_mlx *data)
{
	if (data->mouse_x < 0 || data->mouse_x > WIDTH)
	{
		mlx_mouse_move(data->mlx_win, WIDTH / 2, data->mouse_y);
		data->mouse_x = WIDTH / 2;
	}
	if (data->mouse_y < 0 || data->mouse_y > HEIGHT)
	{
		mlx_mouse_move(data->mlx_win, data->mouse_x, HEIGHT / 2);
		data->mouse_y = HEIGHT / 2;
	}
}

static void	mouse_x_move(t_data_mlx *data, float plane_x, float move_angle_x, \
	float dir_x)
{
	if (move_angle_x > 0)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(-move_angle_x) - \
			data->map->play.dir_y * sin(-move_angle_x);
		data->map->play.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->play.dir_y * cos(-move_angle_x);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-move_angle_x) - \
			data->map->cam.pl_y * sin(-move_angle_x);
		data->map->cam.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->cam.pl_y * cos(-move_angle_x);
		data->map->play.a += -move_angle_x;
	}
	else if (move_angle_x < 0)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(-move_angle_x) - \
			data->map->play.dir_y * sin(-move_angle_x);
		data->map->play.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->play.dir_y * cos(-move_angle_x);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-move_angle_x) - \
			data->map->cam.pl_y * sin(-move_angle_x);
		data->map->cam.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->cam.pl_y * cos(-move_angle_x);
		data->map->play.a += -move_angle_x;
	}
}

void	mouse_move(t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;
	float	move_angle_x;
	float	move_angle_y;

	dir_x = data->map->play.dir_x;
	plane_x = data->map->cam.pl_x;
	mouse_on_screen(data);
	data->prev_mouse_x = data->mouse_x;
	data->prev_mouse_y = data->mouse_y;
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	move_angle_x = data->prev_mouse_x - data->mouse_x;
	move_angle_y = data->prev_mouse_y - data->mouse_y;
	if (move_angle_x > 10)
		move_angle_x = 10;
	if (move_angle_x < -10)
		move_angle_x = -10;
	move_angle_x *= 0.01f;
	move_angle_y *= 6;
	mouse_x_move(data, plane_x, move_angle_x, dir_x);
	if (move_angle_y > 0)
		data->map->cam.vertilcal_pos += move_angle_y;
	else if (move_angle_y < 0)
		data->map->cam.vertilcal_pos += move_angle_y;
}
