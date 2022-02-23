/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/02/23 22:04:00 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	render_next_frame(t_data_mlx *data);

unsigned int	my_mlx_get_pixel(t_data_mlx *data, int x, int y, int wall)
{	
	if (wall == 1)
		return (*(unsigned int *)(data->addr1 + (x * data->bits_per_pixel1 / 8 \
			+ y * data->line_length1)));
	return (0); // in process
}

void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = data->addr + (y * data->line_length + x * \
			(data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_player(t_player *player, t_data_mlx *data)
{
	float	x;
	float	y;

	player->x_textu = player->x * TEXTURESIZE;
	player->y_textu = player->y * TEXTURESIZE;
	x = player->x_textu;
	y = player->y_textu;
	while (x < player->x_textu + (TEXTURESIZE / 2))
	{
		y = player->y_textu;
		while (y < player->y_textu + (TEXTURESIZE / 2))
		{
			my_mlx_pixel_put(data, x - (TEXTURESIZE / 4), \
				y - (TEXTURESIZE / 4), PLAYERCOL);
			y++;
		}
		x++;
	}
}

void	draw_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + TEXTURESIZE)
	{
		j = 0;
		while (y + j < y + TEXTURESIZE)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}	
}

void	line_math(t_data_mlx *data, float rad)
{
	float	c;
	float	ang;
	float	ray_x;
	float	ray_y;
	float	step;

	step = 0.1f;
	c = 0;
	ang = data->map->player.a + rad;
	while (step > 0.00001f)
	{
		while (c < VIEW_RANGE)
		{
			ray_x = data->map->player.x + c * cos(ang);
			ray_y = data->map->player.y + c * sin(ang);
			if (data->map->mapa[(int)ray_y][(int)ray_x].sym != '0')
				break ;
			c += step;
			ray_x *= TEXTURESIZE;
			ray_y *= TEXTURESIZE;
			my_mlx_pixel_put(data, ray_x, ray_y, PLAYERCOL);
		}
		c -= step;
		step /= 2;
	}
	c += step;
}

void	draw_field(int x, int y, t_data_mlx *data)
{
	if (data->map->mapa[x][y].sym == '1')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square(y * TEXTURESIZE, x * TEXTURESIZE, data, FLOORCOL);
}

void	draw_map(t_data_mlx *data)
{
	int		i;
	int		j;
	float	a;

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
	a = ANG_START;
	while (a < FOV)
	{
		line_math(data, a);
		a = a + ANG_STEP;
	}	
}

void	ft_mlx(t_data_mlx *data)
{
	int	img_h;
	int	img_w;

	data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	draw_map_with_move(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	if (data->map->player.f_map)
	{
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx, data->img);
	}
}

int	check_move(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->player.y] \
		[(int)data->map->player.x].sym == '1')
		return (1);
	else
		return (0);
}

int	key_h(int keycode, t_data_mlx *data)
{	
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
	if (keycode == DOWN_KEY)
	{
		data->map->player.x -= MOVE_SPEED * cos(data->map->player.a);
		data->map->player.y -= MOVE_SPEED * sin(data->map->player.a);
		if (check_move(data))
		{
			data->map->player.x += MOVE_SPEED * cos(data->map->player.a);
			data->map->player.y += MOVE_SPEED * sin(data->map->player.a);
		}
	}
	if (keycode == UP_KEY)
	{
		data->map->player.x += MOVE_SPEED * cos(data->map->player.a);
		data->map->player.y += MOVE_SPEED * sin(data->map->player.a);
		if (check_move(data))
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
	render_next_frame(data);
	return (0);
}

int	step_counter_texture(float step, float value)
{
	int		i;
	float	step_buf;

	step_buf = step;
	i = 0;
	while (step < value)
	{
		step += step_buf;
		++i;
	}
	if (i > 256)
		printf("SOMETHING WRONG\n"); // dont forget erase
	return (i);
}

void	draw_ray_catsing(t_data_mlx *data, float x, float height, int w_pixel)
{
	float	i;
	int		j;

	j = 0;
	i = 0 - height / 2;
	while (i < height / 2)
	{
		my_mlx_pixel_put(data, x, HEIGHT / 2 + i, \
			my_mlx_get_pixel(data, w_pixel, \
			step_counter_texture(height / 256, height / 2 + i), 1));
		++i;
	}
}

void	ray_analys(t_data_mlx *data, int c, int x)
{
	float	y;
	int		k;

	k = 20;
	y = HEIGHT / (data->sector[c] * cos(data->ray[c]));
	if (data->sector[c] < VIEW_RANGE)
	{
		if (data->sector_y[c] - (int)data->sector_y[c] <= 0.0001f && \
			data->sector_x[c] - (int)data->sector_x[c] <= 1)
			draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
				data->sector_x[c] - (int)data->sector_x[c]));
			// printf("WHITE");
		else if (data->sector_y[c] - (int)data->sector_y[c] <= 1 && \
			data->sector_x[c] - (int)data->sector_x[c] < 0.0001f)
			draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
				data->sector_y[c] - (int)data->sector_y[c]));
			// printf("RED  ");
		else if (data->sector_y[c] - (int)data->sector_y[c] >= 0.9999f \
			&& data->sector_x[c] - (int)data->sector_x[c] >= 0.0001f)
			draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
				data->sector_x[c] - (int)data->sector_x[c]));
			// printf("GREEN");
		else
			draw_ray_catsing(data, x, y, step_counter_texture(0.00390625f, \
				data->sector_y[c] - (int)data->sector_y[c]));
			// printf("BLUE ");
	}
}

void	draw_fvp(t_data_mlx *data)
{
	int	i;

	i = -1;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	while (++i < ((FOV - ANG_START) / ANG_STEP))
	{
		ray_analys(data, i, i * WIDTH / ((FOV - ANG_START) / ANG_STEP));
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
}

int	render_next_frame(t_data_mlx *data)
{
	int			img_h;
	int			img_w;
	static int	i;

	if (data->map->player.f_map)
	{
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->img = mlx_xpm_file_to_image(data->mlx, \
			"./textures/backgroundmap.xpm", &img_h, &img_w);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx, data->img);
	}
	if (!data->map->player.f_map)
	{
		++i;
		if (i > 39)
			i = 0;
		data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map_with_move(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx, data->img);
		draw_fvp(data);
	}
	// draw map
	return (0);
}

void	init_images(t_data_mlx *data)
{
	int		i;
	char	xpm_path[1024];
	char	*space_dir;
	char	*img_num;
	int		img_h;
	int		img_w;

	i = -1;
	space_dir = "./textures/space_fly/space2/space_fly";
	while (++i < 40)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, space_dir, 1024);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1024);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1024);
		data->image.mm_space[i] = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img_h, &img_w);
	}
	data->img1 = mlx_xpm_file_to_image(data->mlx, "./textures/wall1.xpm", \
		&img_h, &img_w);
	data->addr1 = mlx_get_data_addr(data->img1, &data->bits_per_pixel1, \
		&data->line_length1, &data->endian1);
}

int	draw(t_info *map)
{
	t_data_mlx	data;

	map->player.f_map = 0;
	data.map = map;
	printf("here x = %f y = %f\n", map->player.x, map->player.y);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	init_images(&data);
	ft_mlx(&data);
	render_next_frame(&data);
	// mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
