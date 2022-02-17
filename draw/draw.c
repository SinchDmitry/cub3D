/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/02/17 20:31:25 by aarchiba         ###   ########.fr       */
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
	player->x_textu = player->x * TEXTURESIZE;
	player->y_textu = player->y * TEXTURESIZE;
	float x = player->x_textu;
	float y = player->y_textu;

	while (x < player->x_textu + (TEXTURESIZE / 2))
	{
		y = player->y_textu;
		while (y < player->y_textu + (TEXTURESIZE / 2))
		{
			my_mlx_pixel_put(data, x - (TEXTURESIZE / 4), y - (TEXTURESIZE / 4), PLAYERCOL);
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

void	line_math(t_data_mlx *data)
{
	float	c;
	float	ray_x;
	float	ray_y;

	c = 0;
	while (c < VIEW_RANGE)
	{
		ray_x = data->map->player.x + c * cos(data->map->player.a);
		ray_y = data->map->player.y + c * sin(data->map->player.a);
		if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
			break ;
		ray_x *= TEXTURESIZE;
		ray_y *= TEXTURESIZE;
		c = c + 0.1;
		my_mlx_pixel_put(data, ray_x, ray_y, PLAYERCOL);
	}
}

void draw_field(int x, int y, t_data_mlx *data)
{
	if(data->map->mapa[x][y].sym == '1')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, WALLCOL);
	else if(data->map->mapa[x][y].sym == '0')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, FLOORCOL);
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
			draw_field(i, j, data);
			j++;
		}
		i++;
	}
	draw_player(&data->map->player, data);
	line_math(data);
}

void	ft_mlx(t_data_mlx *data)
{
	// draw 3d
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	// draw minimap
	data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 960, 490);
}

int check_move(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->player.y]
			[(int)data->map->player.x].sym == '1')
	{
		return (1);
	}
	else
		return (0);
}

int	key_h(int keycode, t_data_mlx *data)
{	
	if (keycode == DOWN_KEY)
	{
		data->map->player.x -= MOVE_SPEED * cos(data->map->player.a);
		data->map->player.y -= MOVE_SPEED * sin(data->map->player.a);
		if(check_move(data))
		{
			data->map->player.x += MOVE_SPEED * cos(data->map->player.a);
			data->map->player.y += MOVE_SPEED * sin(data->map->player.a);
		}
	}
	if (keycode == UP_KEY)
	{
		data->map->player.x += MOVE_SPEED * cos(data->map->player.a);
		data->map->player.y += MOVE_SPEED * sin(data->map->player.a);
		if(check_move(data))
		{
			data->map->player.x -= MOVE_SPEED * cos(data->map->player.a);
			data->map->player.y -= MOVE_SPEED * sin(data->map->player.a);
		}
	}
	if (keycode == RIGHT_KEY)
		data->map->player.a += MOVE_ANGLE;
	if (keycode == LEFT_KEY)
		data->map->player.a -= MOVE_ANGLE;
	if (keycode == 53)
		exit(0);
	ft_mlx(data);
	return (0);
}

int	draw(t_info *map)
{
	t_data_mlx data;

	data.map = map;
	printf("here x = %f y = %f\n",map->player.x, map->player.y);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");

	ft_mlx(&data);
	mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
