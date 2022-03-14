/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/14 21:24:50 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	my_mlx_get_pixel(t_data_mlx *data, int x, int y, char side)
{	
	return (*(unsigned int *)(data->wall[side].addr + \
		(x * data->wall[side].bits_per_pixel / 8 + y * data->wall[side].line_length)));
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

int	check_move(t_data_mlx *data)
{
	if (data->map->mapa[(int)data->map->player.y] \
		[(int)data->map->player.x].sym == '1')
		return (1);
	else
		return (0);
}

void	mouse_move(t_data_mlx *data)
{
	float	dir_x;
	float	plane_x;
	float	move_angle_x;
	float	move_angle_y;
	
	dir_x = data->map->player.dir_x;
	plane_x = data->map->camera.pl_x;
	if(data->mouse_x <= 0 || data->mouse_x >= WIDTH)
	{
		mlx_mouse_move(data->mlx_win, WIDTH / 2, HEIGHT / 2);
		data->mouse_x = WIDTH / 2;
	}
	if(data->mouse_y <= 0 || data->mouse_y >= HEIGHT)
	{
		mlx_mouse_move(data->mlx_win, WIDTH / 2, HEIGHT / 2);
		data->mouse_y = HEIGHT / 2;
	}
	data->prev_mouse_x = data->mouse_x;
	data->prev_mouse_y = data->mouse_y;
	
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	move_angle_x = data->prev_mouse_x - data->mouse_x;
	move_angle_y = data->prev_mouse_y - data->mouse_y;
	move_angle_x *= 0.01f;
	move_angle_y *= 6;
	if(move_angle_x > 0)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(-move_angle_x) - \
			data->map->player.dir_y * sin(-move_angle_x);
		data->map->player.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->player.dir_y * cos(-move_angle_x);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(-move_angle_x) - \
			data->map->camera.pl_y * sin(-move_angle_x);
		data->map->camera.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->camera.pl_y * cos(-move_angle_x);
		data->map->player.a += -move_angle_x;
	}
	else if(move_angle_x < 0)
	{
		data->map->player.dir_x = data->map->player.dir_x * cos(-move_angle_x) - \
			data->map->player.dir_y * sin(-move_angle_x);
		data->map->player.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->player.dir_y * cos(-move_angle_x);
		data->map->camera.pl_x = data->map->camera.pl_x * cos(-move_angle_x) - \
			data->map->camera.pl_y * sin(-move_angle_x);
		data->map->camera.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->camera.pl_y * cos(-move_angle_x);
		data->map->player.a += -move_angle_x;
	}
	if(move_angle_y > 0)
	{
		if(data->map->camera.vertilcal_pos)
			data->map->camera.vertilcal_pos += move_angle_y;
	}
	else if(move_angle_y < 0)
	{
		data->map->camera.vertilcal_pos += move_angle_y;
	}
}

int	render_next_frame(t_data_mlx *data)
{
	int			img_h;
	int			img_w;
	static int	i;

	mouse_move(data);
	key_h(data);
	mlx_mouse_hide();
	if (data->map->player.f_map)
	{
		draw_fvp(data);
		if (data->map->player.f_minimap)
			draw_minimap(data);
	}
	if (!data->map->player.f_map)
	{	
		++i;
		if (i > 39)
			i = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, \
			WIDTH / 2 - data->map->width * TEXSIZE / 2, \
			HEIGHT / 2 - data->map->height * TEXSIZE / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
	// printf("x : %d y : %d\n", data->mouse_x, data->mouse_y);
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

	//init animated space
	i = -1;
	space_dir = "./textures/space_fly/space2/space_fly";
	while (++i < 40)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, space_dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);
		data->image.mm_space[i] = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img_h, &img_w);
	}
	//init texure wall
	data->wall[0].img = mlx_xpm_file_to_image(data->mlx, "./textures/wall0.xpm", \
		&data->wall[0].img_h, &data->wall[0].img_w);
	data->wall[0].addr = mlx_get_data_addr(data->wall[0].img, &data->wall[0].bits_per_pixel, \
		&data->wall[0].line_length, &data->wall[0].endian);
	data->wall[1].img = mlx_xpm_file_to_image(data->mlx, "./textures/wall1.xpm", \
		&data->wall[1].img_h, &data->wall[1].img_w);
	data->wall[1].addr = mlx_get_data_addr(data->wall[1].img, &data->wall[1].bits_per_pixel, \
		&data->wall[1].line_length, &data->wall[1].endian);
	data->wall[2].img = mlx_xpm_file_to_image(data->mlx, "./textures/wall2.xpm", \
		&data->wall[2].img_h, &data->wall[2].img_w);
	data->wall[2].addr = mlx_get_data_addr(data->wall[2].img, &data->wall[2].bits_per_pixel, \
		&data->wall[2].line_length, &data->wall[2].endian);
	data->wall[3].img = mlx_xpm_file_to_image(data->mlx, "./textures/wall3.xpm", \
		&data->wall[3].img_h, &data->wall[3].img_w);
	data->wall[3].addr = mlx_get_data_addr(data->wall[3].img, &data->wall[3].bits_per_pixel, \
		&data->wall[3].line_length, &data->wall[3].endian);
		/////
	// data->img1[1] = mlx_xpm_file_to_image(data->mlx, "./textures/wall1.xpm", \
	// 	&img_h, &img_w);
	// data->addr1 = mlx_get_data_addr(data->img1[1], &data->bits_per_pixel1[1], \
	// 	&data->line_length1[1], &data->endian1[1]);
	// data->img1[2] = mlx_xpm_file_to_image(data->mlx, "./textures/wall2.xpm", \
	// 	&img_h, &img_w);
	// data->addr1[2] = mlx_get_data_addr(data->img1[2], &data->bits_per_pixel1[2], \
	// 	&data->line_length1[2], &data->endian1[2]);
	// data->img1[3] = mlx_xpm_file_to_image(data->mlx, "./textures/wall3.xpm", \
	// 	&img_h, &img_w);
	// data->addr1[3] = mlx_get_data_addr(data->img1[3], &data->bits_per_pixel1[3], \
	// 	&data->line_length1[3], &data->endian1[3]);

	//init cpmpas
	data->image.compas = mlx_xpm_file_to_image(data->mlx, "./textures/N.xpm", \
			&img_h, &img_w);
}

int	key_press(int keycode, t_data_mlx *data)
{
	map_exit_case(keycode, data);
	if (keycode >= 0 && keycode < MAX_KEYS_NUM)
		data->keycode[keycode] = PRESS;
	return (0);
}
int	key_unpress(int keycode, t_data_mlx *data)
{
	if (keycode >= 0 && keycode < MAX_KEYS_NUM)
		data->keycode[keycode] = UNPRESS;
	return (0);
}
int	draw(t_info *map)
{
	t_data_mlx	data;
	int i;

	i = 0;
	map->player.f_map = 0;
	map->player.f_minimap = 0;
	data.map = map;
	data.map->camera.vertilcal_pos = 0;
	while(i < MAX_KEYS_NUM)
		data.keycode[i++] = UNPRESS; //init unpress keys
	data.mouse_x = WIDTH / 2;
	data.mouse_y = HEIGHT / 2;
	printf("here x = %f y = %f\n", map->player.x, map->player.y);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	init_images(&data);
	render_next_frame(&data);
	mlx_hook(data.mlx_win, 2, 0, &key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, &key_unpress, &data);
	mlx_mouse_hook(data.mlx_win, &ft_mouse, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	
	// mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
