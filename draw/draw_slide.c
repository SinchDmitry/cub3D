/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 13:42:15 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/24 13:53:57 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	check_move(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->play.y] \
		[(int)data->map->play.x].sym == '1' || \
		data->map->mapa[(int)data->map->play.y] \
		[(int)data->map->play.x].sym == 'e')
		return (1);
	else
		return (0);
}

static void	wall_slide_y(t_data_mlx *data, t_play *player)
{
	float	p_angle;

	p_angle = player->a;
	if ((p_angle >= 0 && p_angle < 1.57f && player->side_for_move == 1) || \
		(p_angle >= 1.57f && p_angle < 3.14f && !player->side_for_move))
	{
		player->y += MOVE_SPEED;
		if (check_move(data))
			player->y -= MOVE_SPEED;
	}
	if ((p_angle >= 4.71f && p_angle < 6.28f && player->side_for_move == 1) || \
		(p_angle >= 3.14f && p_angle < 4.71f && !player->side_for_move))
	{
		player->y -= MOVE_SPEED;
		if (check_move(data))
			player->y += MOVE_SPEED;
	}
}

static void	wall_slide_x(t_data_mlx *data, t_play *player)
{
	float	p_angle;

	p_angle = player->a;
	if ((p_angle >= 0 && p_angle < 1.57f && player->side_for_move == 3) || \
		(p_angle >= 4.71f && p_angle < 6.28f && player->side_for_move == 2))
	{
		player->x += MOVE_SPEED;
		if (check_move(data))
			player->x -= MOVE_SPEED;
	}
	if ((p_angle >= 1.57f && p_angle < 3.14f && player->side_for_move == 3) || \
		(p_angle >= 3.14f && p_angle < 4.71f && player->side_for_move == 2))
	{
		player->x -= MOVE_SPEED;
		if (check_move(data))
			player->x += MOVE_SPEED;
	}
}

void	wall_slide(t_data_mlx *data)
{
	wall_slide_x(data, &data->map->play);
	wall_slide_y(data, &data->map->play);
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