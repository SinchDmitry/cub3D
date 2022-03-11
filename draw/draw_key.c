/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:43:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/11 21:52:44 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ws_case(int keycode, t_data_mlx *data)
{
	if (keycode == S_KEY)
	{
		data->map->player.x -= MOVE_SPEED * data->map->player.dir_x;
		data->map->player.y -= MOVE_SPEED * data->map->player.dir_y;
		if (check_move(data))
		{
			data->map->player.x += MOVE_SPEED * data->map->player.dir_x;
			data->map->player.y += MOVE_SPEED * data->map->player.dir_y;
		}
	}
	if (keycode == W_KEY)
	{
		data->map->player.x += MOVE_SPEED * data->map->player.dir_x;
		data->map->player.y += MOVE_SPEED * data->map->player.dir_y;
		if (check_move(data))
		{
			data->map->player.x -= MOVE_SPEED * data->map->player.dir_x;
			data->map->player.y -= MOVE_SPEED * data->map->player.dir_y;
		}
	}
}

static void	ad_case(int keycode, t_data_mlx *data)
{
	if (keycode == D_KEY)
	{
		data->map->player.x -= MOVE_SPEED * (data->map->player.dir_y);
		data->map->player.y += MOVE_SPEED * (data->map->player.dir_x);
		if (check_move(data))
		{
			data->map->player.x += MOVE_SPEED * (data->map->player.dir_y);
			data->map->player.y += MOVE_SPEED * (data->map->player.dir_x);
		}
	}
	if (keycode == A_KEY)
	{
		data->map->player.x += MOVE_SPEED * (data->map->player.dir_y);
		data->map->player.y -= MOVE_SPEED * (data->map->player.dir_x);
		if (check_move(data))
		{
			data->map->player.x -= MOVE_SPEED * (data->map->player.dir_y);
			data->map->player.y -= MOVE_SPEED * (data->map->player.dir_x);
		}
	}
}

static void	rl_case(int keycode, t_data_mlx *data, float dir_x, float plane_x)
{
	dir_x = data->map->player.dir_x;
	plane_x = data->map->camera.pl_x;
	if (keycode == LEFT_KEY)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(-MOVE_ANGLE) - \
			data->map->player.dir_y * sin(-MOVE_ANGLE);
		data->map->player.dir_y = dir_x * sin(-MOVE_ANGLE) + \
			data->map->player.dir_y * cos(-MOVE_ANGLE);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(-MOVE_ANGLE) - \
			data->map->camera.pl_y * sin(-MOVE_ANGLE);
		data->map->camera.pl_y = plane_x * sin(-MOVE_ANGLE) + \
			data->map->camera.pl_y * cos(-MOVE_ANGLE);
		data->map->player.a += -MOVE_ANGLE;
	}
	if (keycode == RIGHT_KEY)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(MOVE_ANGLE) - \
			data->map->player.dir_y * sin(MOVE_ANGLE);
		data->map->player.dir_y = dir_x * sin(MOVE_ANGLE) + \
			data->map->player.dir_y * cos(MOVE_ANGLE);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(MOVE_ANGLE) - \
			data->map->camera.pl_y * sin(MOVE_ANGLE);
		data->map->camera.pl_y = plane_x * sin(MOVE_ANGLE) + \
			data->map->camera.pl_y * cos(MOVE_ANGLE);
		data->map->player.a += MOVE_ANGLE;
	}
}

static void	map_exit_case(int keycode, t_data_mlx *data)
{
	if (keycode == MINIMAP_KEY)
	{
		if (data->map->player.f_minimap)
		{
			mlx_clear_window(data->mlx, data->mlx_win);
			data->map->player.f_minimap = 0;
		}
		else
			data->map->player.f_minimap = 1;
	}
	if (keycode == MAP_KEY)
	{
		if (data->map->player.f_map)
		{
			mlx_clear_window(data->mlx, data->mlx_win);
			data->map->player.f_map = 0;
		}
		else
			data->map->player.f_map = 1;
	}
	if (keycode == 53)
		exit(0);
}

int	key_h(int keycode, t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;

	map_exit_case(keycode, data);
	ws_case(keycode, data);
	ad_case(keycode, data);
	rl_case(keycode, data, dir_x, plane_x);
	render_next_frame(data);
	return (0);
}
