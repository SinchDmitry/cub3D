/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/13 13:38:47 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	my_mlx_get_pixel(t_data_mlx *data, int x, int y, char side)
{	
	int	wall;

	wall = 0;
	if (side == 'W')
		wall = 0;
	if (side == 'E')
		wall = 1;
	if (side == 'N')
		wall = 2;
	if (side == 'S')
		wall = 3;
	return (*(unsigned int *)(data->addr1[wall] + (x * data->bits_per_pixel1[wall] / 8 \
			+ y * data->line_length1[wall])));
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
	data->prev_mouse_x = data->mouse_x;
	data->prev_mouse_y = data->mouse_y;
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	if(data->prev_mouse_x > data->mouse_x)
	{
		data->keycode[LEFT_KEY] = PRESS;
	}
	else if(data->prev_mouse_x < data->mouse_x)
	{
		data->keycode[RIGHT_KEY] = PRESS;
	}
	else
	{
		data->keycode[LEFT_KEY] = UNPRESS;
		data->keycode[RIGHT_KEY] = UNPRESS;
	}
	if(data->prev_mouse_y > data->mouse_y)
	{
		data->keycode[Q_KEY] = PRESS;
	}
	else if(data->prev_mouse_y < data->mouse_y)
	{
		data->keycode[E_KEY] = PRESS;
	}
	else
	{
		data->keycode[Q_KEY] = UNPRESS;
		data->keycode[E_KEY] = UNPRESS;
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
		{	
			draw_minimap(data);
		}
	}
	if (!data->map->player.f_map)
	{	
		++i;
		if (i > 39)
			i = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, WIDTH / 2 - data->map->width * TEXSIZE / 2, HEIGHT / 2 - data->map->height * TEXSIZE / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
	printf("x : %d y : %d\n", data->mouse_x, data->mouse_y);
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
		ft_strlcat(xpm_path, space_dir, 1024);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1024);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1024);
		data->image.mm_space[i] = mlx_xpm_file_to_image(data->mlx, xpm_path, \
			&img_h, &img_w);
	}
	//init texure wall
	data->img1[0] = mlx_xpm_file_to_image(data->mlx, "./textures/wall0.xpm", \
		&img_h, &img_w);
	data->addr1[0] = mlx_get_data_addr(data->img1[0], &data->bits_per_pixel1[0], \
		&data->line_length1[0], &data->endian1[0]);
	data->img1[1] = mlx_xpm_file_to_image(data->mlx, "./textures/wall1.xpm", \
		&img_h, &img_w);
	data->addr1[1] = mlx_get_data_addr(data->img1[1], &data->bits_per_pixel1[1], \
		&data->line_length1[1], &data->endian1[1]);
	data->img1[2] = mlx_xpm_file_to_image(data->mlx, "./textures/wall2.xpm", \
		&img_h, &img_w);
	data->addr1[2] = mlx_get_data_addr(data->img1[2], &data->bits_per_pixel1[2], \
		&data->line_length1[2], &data->endian1[2]);
	data->img1[3] = mlx_xpm_file_to_image(data->mlx, "./textures/wall3.xpm", \
		&img_h, &img_w);
	data->addr1[3] = mlx_get_data_addr(data->img1[3], &data->bits_per_pixel1[3], \
		&data->line_length1[3], &data->endian1[3]);


	
	//init cpmpas
	data->image.compas[0] = mlx_xpm_file_to_image(data->mlx, "./textures/N.xpm", \
			&img_h, &img_w);
	// data->image.compas[1] = mlx_xpm_file_to_image(data->mlx, "./textures/E.xpm", \
	// 		&img_h, &img_w);
	// data->image.compas[2] = mlx_xpm_file_to_image(data->mlx, "./textures/W.xpm", \
	// 		&img_h, &img_w);
	// data->image.compas[3] = mlx_xpm_file_to_image(data->mlx, "./textures/S.xpm", \
	// 		&img_h, &img_w);
}

int	key_press(int keycode, t_data_mlx *data)
{
	map_exit_case(keycode, data);
	if (keycode >= 0 && keycode < 250)
		data->keycode[keycode] = PRESS;
	return (0);
}
int	key_unpress(int keycode, t_data_mlx *data)
{
	if (keycode >= 0 && keycode < 250)
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
	while(i < 250)
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
