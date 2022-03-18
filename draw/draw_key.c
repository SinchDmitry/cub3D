/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:43:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/18 13:42:33 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ws_case(t_data_mlx *data)
{
	float move_speed;

	move_speed = MOVE_SPEED;
	if (data->keycode[SHIFT_KEY] == PRESS)
		move_speed *= 1.5f; 
	if (data->keycode[S_KEY] == PRESS)
	{
		data->map->player.x -= move_speed * data->map->player.dir_x;
		data->map->player.y -= move_speed * data->map->player.dir_y;
		if (check_move(data))
		{
			data->map->player.x += move_speed * data->map->player.dir_x;
			data->map->player.y += move_speed * data->map->player.dir_y;
		}
	}
	if (data->keycode[W_KEY] == PRESS)
	{
		data->map->player.x += move_speed * data->map->player.dir_x;
		data->map->player.y += move_speed * data->map->player.dir_y;
		if (check_move(data))
		{
			data->map->player.x -= move_speed * data->map->player.dir_x;
			data->map->player.y -= move_speed * data->map->player.dir_y;
		}
	}
}

static void	ad_case(t_data_mlx *data)
{
	if (data->keycode[D_KEY] == PRESS)
	{
		data->map->player.x -= MOVE_SPEED * (data->map->player.dir_y);
		data->map->player.y += MOVE_SPEED * (data->map->player.dir_x);
		if (check_move(data))
		{
			data->map->player.x += MOVE_SPEED * (data->map->player.dir_y);
			data->map->player.y += MOVE_SPEED * (data->map->player.dir_x);
		}
	}
	if (data->keycode[A_KEY] == PRESS)
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

static void	rl_case(t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;
		
	dir_x = data->map->player.dir_x;
	plane_x = data->map->camera.pl_x;
	if (data->keycode[LEFT_KEY] == PRESS)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(-MOVE_ANGLE) - \
			data->map->player.dir_y * sin(-MOVE_ANGLE);
		data->map->player.dir_y = dir_x * sin(-MOVE_ANGLE) + \
			data->map->player.dir_y * cos(-MOVE_ANGLE);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(-MOVE_ANGLE) - \
			data->map->camera.pl_y * sin(-MOVE_ANGLE);
		data->map->camera.pl_y = plane_x * sin(-MOVE_ANGLE) + \
			data->map->camera.pl_y * cos(-MOVE_ANGLE);
		data->map->player.a -= MOVE_ANGLE;
	}
	if (data->keycode[RIGHT_KEY] == PRESS)
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

void	map_exit_case(int keycode, t_data_mlx *data)
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

static void	qe_case(t_data_mlx *data)
{
	if (data->keycode[Q_KEY] == PRESS)
	{
		data->map->camera.vertilcal_pos += 15;
	}
	if (data->keycode[E_KEY] == PRESS)
	{
		data->map->camera.vertilcal_pos -= 15;
	}
}

int	key_h(t_data_mlx *data)
{
	ws_case(data);
	ad_case(data);
	rl_case(data);
	qe_case(data);
	// render_next_frame(data);
	return (0);
}
