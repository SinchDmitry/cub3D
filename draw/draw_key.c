/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:43:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/02 17:11:09 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	ws_case(t_data_mlx *data, float move_speed)
{
	if (data->keycode[SHIFT_KEY] == PRESS)
		move_speed *= 1.5f;
	if (data->keycode[S_KEY] == PRESS)
	{
		data->map->play.x -= move_speed * data->map->play.dir_x;
		data->map->play.y -= move_speed * data->map->play.dir_y;
		if (check_move(data))
		{
			data->map->play.x += move_speed * data->map->play.dir_x;
			data->map->play.y += move_speed * data->map->play.dir_y;
		}
	}
	if (data->keycode[W_KEY] == PRESS)
	{
		data->map->play.x += move_speed * data->map->play.dir_x;
		data->map->play.y += move_speed * data->map->play.dir_y;
		if (check_move(data))
		{
			data->map->play.x -= move_speed * data->map->play.dir_x;
			data->map->play.y -= move_speed * data->map->play.dir_y;
			wall_slide(data);
		}
	}
}

static void	ad_case(t_data_mlx *data)
{
	if (data->keycode[D_KEY] == PRESS)
	{
		data->map->play.x -= MOVE_SPEED * (data->map->play.dir_y);
		data->map->play.y += MOVE_SPEED * (data->map->play.dir_x);
		if (check_move(data))
		{
			data->map->play.x += MOVE_SPEED * (data->map->play.dir_y);
			data->map->play.y -= MOVE_SPEED * (data->map->play.dir_x);
		}
	}
	if (data->keycode[A_KEY] == PRESS)
	{
		data->map->play.x += MOVE_SPEED * (data->map->play.dir_y);
		data->map->play.y -= MOVE_SPEED * (data->map->play.dir_x);
		if (check_move(data))
		{
			data->map->play.x -= MOVE_SPEED * (data->map->play.dir_y);
			data->map->play.y += MOVE_SPEED * (data->map->play.dir_x);
		}
	}
}

static void	rl_case(t_data_mlx *data, t_play *pl)
{
	float	dir_x;
	float	plane_x;

	dir_x = pl->dir_x;
	plane_x = data->map->cam.pl_x;
	if (data->keycode[LEFT_KEY] == PRESS)
	{
		pl->dir_x = pl->dir_x * cos(-MOVE_ANGLE) - pl->dir_y * sin(-MOVE_ANGLE);
		pl->dir_y = dir_x * sin(-MOVE_ANGLE) + pl->dir_y * cos(-MOVE_ANGLE);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-MOVE_ANGLE) - \
			data->map->cam.pl_y * sin(-MOVE_ANGLE);
		data->map->cam.pl_y = plane_x * sin(-MOVE_ANGLE) + \
			data->map->cam.pl_y * cos(-MOVE_ANGLE);
		pl->a -= MOVE_ANGLE;
	}
	if (data->keycode[RIGHT_KEY] == PRESS)
	{
		pl->dir_x = pl->dir_x * cos(MOVE_ANGLE) - pl->dir_y * sin(MOVE_ANGLE);
		pl->dir_y = dir_x * sin(MOVE_ANGLE) + pl->dir_y * cos(MOVE_ANGLE);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(MOVE_ANGLE) - \
			data->map->cam.pl_y * sin(MOVE_ANGLE);
		data->map->cam.pl_y = plane_x * sin(MOVE_ANGLE) + \
			data->map->cam.pl_y * cos(MOVE_ANGLE);
		pl->a += MOVE_ANGLE;
	}
}

int	key_h(t_data_mlx *data)
{
	if (data->map->play.a < 0)
		data->map->play.a = 6.28f;
	else if (data->map->play.a > 6.28f)
		data->map->play.a = 0;
	ws_case(data, MOVE_SPEED);
	ad_case(data);
	rl_case(data, &data->map->play);
	return (0);
}
