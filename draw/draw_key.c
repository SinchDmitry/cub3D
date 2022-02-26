/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:43:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/26 14:27:54 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	ws_case(int keycode, t_data_mlx *data)
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

void	ad_case(int keycode, t_data_mlx *data)
{
	int	ang;

	ang = tan(1.571f / 2);
	if (keycode == A_KEY)
	{
		data->map->player.x -= MOVE_SPEED * (data->map->player.dir_x - ang);
		data->map->player.y -= MOVE_SPEED * (data->map->player.dir_y - ang);
		if (check_move(data))
		{
			data->map->player.x += MOVE_SPEED * (data->map->player.dir_x - ang);
			data->map->player.y += MOVE_SPEED * (data->map->player.dir_y - ang);
		}
	}
	if (keycode == D_KEY)
	{
		data->map->player.x += MOVE_SPEED * (data->map->player.dir_x - ang);
		data->map->player.y += MOVE_SPEED * (data->map->player.dir_y - ang);
		if (check_move(data))
		{
			data->map->player.x -= MOVE_SPEED * (data->map->player.dir_x - ang);
			data->map->player.y -= MOVE_SPEED * (data->map->player.dir_y - ang);
		}
	}
}

void	rl_case(int keycode, t_data_mlx *data, float dir_x, float plane_x)
{
	dir_x = data->map->player.dir_x;
	plane_x = data->map->camera.pl_x;
	if (keycode == RIGHT_KEY)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(-MOVE_ANGLE) - \
			data->map->player.dir_y * sin(-MOVE_ANGLE);
		data->map->player.dir_y = dir_x * sin(-MOVE_ANGLE) + \
			data->map->player.dir_y * cos(-MOVE_ANGLE);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(-MOVE_ANGLE) - \
			data->map->camera.pl_y * sin(-MOVE_ANGLE);
		data->map->camera.pl_y = plane_x * sin(-MOVE_ANGLE) + \
			data->map->camera.pl_y * cos(-MOVE_ANGLE);
	}
	if (keycode == LEFT_KEY)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(MOVE_ANGLE) - \
			data->map->player.dir_y * sin(MOVE_ANGLE);
		data->map->player.dir_y = dir_x * sin(MOVE_ANGLE) + \
			data->map->player.dir_y * cos(MOVE_ANGLE);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(MOVE_ANGLE) - \
			data->map->camera.pl_y * sin(MOVE_ANGLE);
		data->map->camera.pl_y = plane_x * sin(MOVE_ANGLE) + \
			data->map->camera.pl_y * cos(MOVE_ANGLE);
	}
}

void map_zoom()
{
	
}

int	key_h(int keycode, t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;
	printf("%d\n", keycode);
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
	ws_case(keycode, data);
	ad_case(keycode, data);
	rl_case(keycode, data, dir_x, plane_x);
	if (keycode == 53)
		exit(0);
	render_next_frame(data);
	return (0);
}
