/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:28:30 by utygett           #+#    #+#             */
/*   Updated: 2022/04/02 18:12:25 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	check_player_in_door(t_data_mlx *data, int i, int j)
{
	if (i == (int)data->map->play.y && j == \
		(int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i + 1 == (int)data->map->play.y && j == \
		(int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i + -1 == (int)data->map->play.y && j == \
		(int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i == (int)data->map->play.y && j + 1 == \
		(int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (i == (int)data->map->play.y && j - 1 == \
		(int)data->map->play.x && data->map->mapa[i][j].door < 0)
		data->map->mapa[i][j].door = -2;
	else if (data->map->mapa[i][j].door == -2)
		data->map->mapa[i][j].door = 2;
}

void	check_door_state(t_data_mlx *data, t_par_slot **mapa)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (mapa[i][j].door_state > 0 && mapa[i][j].door_state < 10 && \
					mapa[i][j].door == 1)
				++mapa[i][j].door_state;
			if (mapa[i][j].door_state > 0 && mapa[i][j].door_state <= 10 && \
					mapa[i][j].door == 2)
				--mapa[i][j].door_state;
			if (mapa[i][j].door_state >= 10)
			{
				if (mapa[i][j].door > 0)
					mapa[i][j].door = -1;
				check_player_in_door(data, i, j);
			}
			if (mapa[i][j].door_state == 0 && mapa[i][j].door == 2)
				mapa[i][j].door = 1;
		}
	}
}

static void	draw_door(t_data_mlx *data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		if (data->door_str[x].use)
		{
			while (++data->door_str[x].start < data->door_str[x].end)
			{
				data->door_str[x].text_y = (int)data->door_str[x].tex_pos \
				& (data->am_s->door_tex[0].img_h - 1);
				data->door_str[x].tex_pos += data->door_str[x].step;
				my_mlx_pixel_put(data, x, data->door_str[x].start, \
					my_mlx_get_pixel(data->am_s->door_tex[data->door_str[x] \
						.door_state], data->door_str[x].text_x, \
						data->door_str[x].text_y));
			}
			data->door_str[x].use = 0;
		}
		data->door_str[x].use = 0;
	}
}

void	check_door(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->play.y + \
		1][(int)data->map->play.x].door == 1 && data->keycode[E_KEY] \
			&& data->map->mapa[(int)data->map->play.y + \
				1][(int)data->map->play.x].door_state == 0)
		data->map->mapa[(int)data->map->play.y + \
			1][(int)data->map->play.x].door_state = 1;
	else if (data->map->mapa[(int)data->map->play.y - \
		1][(int)data->map->play.x].door == 1 && data->keycode[E_KEY] \
			&& data->map->mapa[(int)data->map->play.y - \
			1][(int)data->map->play.x].door_state == 0)
		data->map->mapa[(int)data->map->play.y - \
			1][(int)data->map->play.x].door_state = 1;
	else if (data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + \
		1].door == 1 && data->keycode[E_KEY] && \
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + \
		1].door_state == 0)
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x + \
			1].door_state = 1;
	else if (data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - \
		1].door == 1 && data->keycode[E_KEY] && \
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - \
		1].door_state == 0)
		data->map->mapa[(int)data->map->play.y][(int)data->map->play.x - \
			1].door_state = 1;
	draw_door(data);
}
