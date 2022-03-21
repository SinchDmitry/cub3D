/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:43:17 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/20 17:43:32 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	wall_slide(t_data_mlx *data)
{
	// data->map->play.a = fabsf(fmodf(data->map->play.a, 6.28f));
	// float player_angle = fabsf(fmodf(data->map->play.a, 6.28f));
	float player_angle = data->map->play.a;

	// printf("a : %f\n", data->map->play.a);
	// printf("a : %f\n", player_angle);
	// printf("side : %d\n", data->map->play.side_for_move);
	if (player_angle >= 0 && player_angle < 1.57f && data->map->play.side_for_move == 1)
		data->map->play.y += MOVE_SPEED;
	if (player_angle >= 4.71f && player_angle < 6.28f && data->map->play.side_for_move == 1)
		data->map->play.y -= MOVE_SPEED;
	if (player_angle >= 1.57f && player_angle < 3.14f && data->map->play.side_for_move == 0)
		data->map->play.y += MOVE_SPEED;
	if (player_angle >= 3.14f  && player_angle < 4.71f && data->map->play.side_for_move == 0)
		data->map->play.y -= MOVE_SPEED;
	if (player_angle >= 0 && player_angle < 1.57f && data->map->play.side_for_move == 3)
		data->map->play.x += MOVE_SPEED;
	if (player_angle >= 1.57f && player_angle < 3.14f && data->map->play.side_for_move == 3)
		data->map->play.x -= MOVE_SPEED;
	if (player_angle >= 4.71f && player_angle < 6.28f && data->map->play.side_for_move == 2)
		data->map->play.x += MOVE_SPEED;
	if (player_angle >= 3.14f && player_angle < 4.71f && data->map->play.side_for_move == 2)
		data->map->play.x -= MOVE_SPEED;
	// else if (player_angle >=  1.57f && player_angle < 3.14f)
	// 	data->map->play.y -= MOVE_SPEED;
	// else if (player_angle >= 3.14f && player_angle < 4.71f)
	// 	data->map->play.y -= MOVE_SPEED;
	// else if (player_angle >= 4.71f && player_angle < 6.28f)
	// 	data->map->play.y += MOVE_SPEED;
}	


static void	ws_case(t_data_mlx *data)
{
	float move_speed;

	move_speed = MOVE_SPEED;
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
			data->map->play.y += MOVE_SPEED * (data->map->play.dir_x);
		}
	}
	if (data->keycode[A_KEY] == PRESS)
	{
		data->map->play.x += MOVE_SPEED * (data->map->play.dir_y);
		data->map->play.y -= MOVE_SPEED * (data->map->play.dir_x);
		if (check_move(data))
		{
			data->map->play.x -= MOVE_SPEED * (data->map->play.dir_y);
			data->map->play.y -= MOVE_SPEED * (data->map->play.dir_x);
		}
	}
}

static void	rl_case(t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;
		
	dir_x = data->map->play.dir_x;
	plane_x = data->map->cam.pl_x;
	if (data->keycode[LEFT_KEY] == PRESS)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(-MOVE_ANGLE) - \
			data->map->play.dir_y * sin(-MOVE_ANGLE);
		data->map->play.dir_y = dir_x * sin(-MOVE_ANGLE) + \
			data->map->play.dir_y * cos(-MOVE_ANGLE);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-MOVE_ANGLE) - \
			data->map->cam.pl_y * sin(-MOVE_ANGLE);
		data->map->cam.pl_y = plane_x * sin(-MOVE_ANGLE) + \
			data->map->cam.pl_y * cos(-MOVE_ANGLE);
		data->map->play.a -= MOVE_ANGLE;
	}
	if (data->keycode[RIGHT_KEY] == PRESS)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(MOVE_ANGLE) - \
			data->map->play.dir_y * sin(MOVE_ANGLE);
		data->map->play.dir_y = dir_x * sin(MOVE_ANGLE) + \
			data->map->play.dir_y * cos(MOVE_ANGLE);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(MOVE_ANGLE) - \
			data->map->cam.pl_y * sin(MOVE_ANGLE);
		data->map->cam.pl_y = plane_x * sin(MOVE_ANGLE) + \
			data->map->cam.pl_y * cos(MOVE_ANGLE);
		data->map->play.a += MOVE_ANGLE;
	}
}

void	map_exit_case(int keycode, t_data_mlx *data)
{
	if (keycode == MINIMAP_KEY)
	{
		if (data->map->play.f_minimap)
		{
			mlx_clear_window(data->mlx, data->mlx_win);
			data->map->play.f_minimap = 0;
		}
		else
			data->map->play.f_minimap = 1;
	}
	if (keycode == MAP_KEY)
	{
		if (data->map->play.f_map)
		{
			mlx_clear_window(data->mlx, data->mlx_win);
			data->map->play.f_map = 0;
		}
		else
			data->map->play.f_map = 1;
	}
	if (keycode == 53)
		exit(0);
}

static void	qe_case(t_data_mlx *data)
{
	if (data->keycode[Q_KEY] == PRESS)
	{
		data->map->cam.vertilcal_pos += 15;
	}
	if (data->keycode[E_KEY] == PRESS)
	{
		data->map->cam.vertilcal_pos -= 15;
	}
}

int	key_h(t_data_mlx *data)
{
	if (data->map->play.a < 0)
		data->map->play.a = 6.28f;
	else if (data->map->play.a > 6.28f)
		data->map->play.a = 0;
	ws_case(data);
	ad_case(data);
	rl_case(data);
	qe_case(data);
	// render_next_frame(data);
	return (0);
}
