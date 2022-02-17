/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/02/17 16:44:51 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_player(t_player *player , t_data_mlx *data)
{
	float x = player->x;
	float y = player->y;
	while (x < player->x + 10)
	{
		y = player->y;
		while (y < player->y + 10)
		{
			my_mlx_pixel_put(data, x - 5, y - 5, PLAYERCOL);
			y++;
		}
		x++;
	}
		
}

void draw_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i <  x + TEXTURESIZE)
	{
		j = 0;
		while (y + j <  y + TEXTURESIZE)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
	
}

void draw_field(int x, int y, t_data_mlx *data)
{
	if(data->map->mapa[x][y].sym == '1')
		draw_square(x * TEXTURESIZE, y * TEXTURESIZE, data, WALLCOL);
	else if(data->map->mapa[x][y].sym == '0')
		draw_square(x * TEXTURESIZE, y * TEXTURESIZE, data, FLOORCOL);
}

void draw_map(t_data_mlx *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			j++;
			draw_field(i, j, data);
		}
		i++;
	}
	
}

void	ft_mlx(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length,
			&data->endian);
	draw_map(data);
	draw_player(&data->player, data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
}

#define MOVE_SPEED 5
int	key_h(int keycode, t_data_mlx *data)
{	
	if (keycode == 126)
		data->player.y -= MOVE_SPEED;
	if (keycode == 125)
		data->player.y += MOVE_SPEED;
	if (keycode == 124)
		data->player.x += MOVE_SPEED;
	if (keycode == 123)
		data->player.x -= MOVE_SPEED;
	if (keycode == 53)
		exit(0);
	ft_mlx(data);
	return (0);
}


int	draw(t_info *map)
{
	t_data_mlx data;

	data.map = map;
	data.player.x = 15;
	data.player.y = 15;
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");

	ft_mlx(&data);
	mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
