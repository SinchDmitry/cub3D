/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 11:50:19 by utygett           #+#    #+#             */
/*   Updated: 2022/02/23 22:06:13 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	pixel_put_map_move(int x, int y, t_data_mlx *data, int color)
{
	float	x1;
	float	y1;
	float	h;
	float	w;

	x1 = x;
	y1 = y;
	h = ((data->map->player.x) * MMTEXTURESIZE);
	w = ((data->map->player.y) * MMTEXTURESIZE);
	x = ((x1 - h) * sin(data->map->player.a + ROTATE_MOV) - (y1 - w) * \
		cos(data->map->player.a + ROTATE_MOV));
	y = ((x1 - h) * cos(data->map->player.a + ROTATE_MOV) + (y1 - w) * \
		sin(data->map->player.a + ROTATE_MOV));
	if (x + MOVEX < MINIMAPHEIGHT && y + MOVEY < MINIMAPWIDTH && \
		x + MOVEX > 0 && y + MOVEY > 0)
		my_mlx_pixel_put(data, x + MOVEX, y + MOVEY, color);
}

void	draw_square_move(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + MMTEXTURESIZE)
	{
		j = 0;
		while (y + j < y + MMTEXTURESIZE)
		{	
			pixel_put_map_move(x + i, y + j, data, color);
			j++;
		}
		i++;
	}
}

void	draw_invis_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + MMTEXTURESIZE)
	{
		j = 0;
		while (y + j < y + MMTEXTURESIZE)
		{	
			my_mlx_pixel_put(data, y, x, color);
			j++;
		}
		i++;
	}
}

void	draw_field_move(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square_move(y * MMTEXTURESIZE, x * MMTEXTURESIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square_move(y * MMTEXTURESIZE, x * MMTEXTURESIZE, data, FLOORCOL);
}

void	draw_player_move(t_player *player, t_data_mlx *data)
{
	float	x;
	float	y;

	player->x_textu = player->x * MMTEXTURESIZE;
	player->y_textu = player->y * MMTEXTURESIZE;
	x = player->x_textu;
	y = player->y_textu;
	while (x < player->x_textu + (MMTEXTURESIZE / 2))
	{
		y = player->y_textu;
		while (y < player->y_textu + (MMTEXTURESIZE / 2))
		{
			pixel_put_map_move(x - (MMTEXTURESIZE / 4), \
				y - (MMTEXTURESIZE / 4), data, PLAYERCOL);
			y++;
		}
		x++;
	}
}

void	line_math_move(t_data_mlx *data, int i)
{
	float	c;
	float	ang;
	float	ray_x;
	float	ray_y;
	float	step;

	step = 0.1f;
	c = 0;
	ang = data->map->player.a + data->ray_a;
	while (step > 0.00001f)
	{
		while (c < VIEW_RANGE)
		{
			ray_x = data->map->player.x + c * cos(ang);
			ray_y = data->map->player.y + c * sin(ang);
			if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
				break ;
			c = c + step;
		}
		c -= step;
		step /= 2;
	}
	c = c + step;
	data->ray[i] = data->ray_a;
	data->sector[i] = c;
	data->sector_x[i] = ray_x;
	data->sector_y[i] = ray_y;
}

void	draw_invis_background(t_data_mlx *data, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{	
			my_mlx_pixel_put(data, i , j , INVISIBLE_COL);
			j++;
		}
		i++;
	}
}

void	draw_board(t_data_mlx *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAPHEIGHT)
	{
		j = 0;
		while (j < MINIMAPWIDTH)
		{	
			if (i <= MM_BOARD_SIZE || i >= MINIMAPHEIGHT - MM_BOARD_SIZE)
				my_mlx_pixel_put(data, i , j , MM_BOARD_COL);
			else if (j <= MM_BOARD_SIZE || j >= MINIMAPWIDTH - MM_BOARD_SIZE)
				my_mlx_pixel_put(data, i , j , MM_BOARD_COL);
			j++;
		}
		i++;
	}
}

void	draw_map_with_move(t_data_mlx *data)
{
	int	i;
	int	j;

	i = 0;
	draw_invis_background(data, MINIMAPHEIGHT, MINIMAPWIDTH);
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			draw_field_move(i, j, data);
			j++;
		}
		i++;
	}
	draw_player_move(&data->map->player, data);
	data->ray_a = ANG_START;
	i = 0;
	while (data->ray_a <= FOV)
	{
		line_math_move(data, i);
		data->ray_a = data->ray_a + ANG_STEP;
		i++;
	}
	draw_board(data);
}
