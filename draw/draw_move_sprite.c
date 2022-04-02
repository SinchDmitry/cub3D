/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_move_sprite.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:09:14 by utygett           #+#    #+#             */
/*   Updated: 2022/04/02 20:27:59 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static int	check_move_sprite(t_data_mlx *data, int x, int y)
{
	if (data->map->mapa[y][x].sym == '1' || \
		data->map->mapa[y][x].sym == 'e' || data->map->mapa[y][x].door > 0)
		return (1);
	else
		return (0);
}

static void	move_sprite_a(t_data_mlx *data, t_spr_tex *tmp_img)
{
	if (tmp_img->move_flag == 0)
	{
		tmp_img->x += MOVE_STEP_SPRITE;
		if (check_move_sprite(data, tmp_img->x + WALL_COLLISION, tmp_img->y))
		{
			tmp_img->x -= MOVE_STEP_SPRITE;
			tmp_img->move_flag = data->frame_num % 4;
		}
	}
	else if (tmp_img->move_flag == 1)
	{
		tmp_img->y -= MOVE_STEP_SPRITE;
		if (check_move_sprite(data, tmp_img->x, tmp_img->y - WALL_COLLISION))
		{
			tmp_img->y += MOVE_STEP_SPRITE;
			tmp_img->move_flag = data->frame_num % 4;
		}
	}
}

static void	move_sprite_b(t_data_mlx *data, t_spr_tex *tmp_img)
{
	if (tmp_img->move_flag == 2)
	{
		tmp_img->x -= MOVE_STEP_SPRITE;
		if (check_move_sprite(data, tmp_img->x - WALL_COLLISION, tmp_img->y))
		{
			tmp_img->x += MOVE_STEP_SPRITE;
			tmp_img->move_flag = data->frame_num % 4;
		}
	}
	else if (tmp_img->move_flag == 3)
	{
		tmp_img->y += MOVE_STEP_SPRITE;
		if (check_move_sprite(data, tmp_img->x, tmp_img->y + WALL_COLLISION))
		{
			tmp_img->y -= MOVE_STEP_SPRITE;
			tmp_img->move_flag = data->frame_num % 4;
		}
	}
}

void	check_sprite_position(t_data_mlx *data)
{
	t_spr_tex	*tmp_img;

	tmp_img = data->am_s->spr_img;
	while (tmp_img)
	{	
		if (!tmp_img->dead)
		{
			move_sprite_a(data, tmp_img);
			move_sprite_b(data, tmp_img);
		}
		tmp_img = tmp_img->next;
	}
}
