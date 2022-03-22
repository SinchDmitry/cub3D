/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/22 16:54:26 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

unsigned int	my_mlx_get_pixel(t_data_mlx *data, int x, int y, char side)
{	
	if (side > 3)
	{
		return (*(unsigned int *)(data->am_s->spr_img[side - 10].costumes[data->am_s->spr_img[side - 10].c_num].addr + \
			(x * data->am_s->spr_img[side - 10].costumes[data->am_s->spr_img[side - 10].c_num].bits_per_pixel / 8 + \
			y * data->am_s->spr_img[side - 10].costumes[data->am_s->spr_img[side - 10].c_num].line_length)));
	}
	else
	{
		return (*(unsigned int *)(data->wall[side].addr + \
		(x * data->wall[side].bits_per_pixel / 8 + y * data->wall[side].line_length)));
	}
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
	if (data->map->mapa[(int)data->map->play.y] \
		[(int)data->map->play.x].sym == '1')
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
	
	dir_x = data->map->play.dir_x;
	plane_x = data->map->cam.pl_x;
	if (data->mouse_x < 0 || data->mouse_x > WIDTH)
	{
		mlx_mouse_move(data->mlx_win, WIDTH / 2, data->mouse_y);
		data->mouse_x = WIDTH / 2;
	}
	if (data->mouse_y < 0 || data->mouse_y > HEIGHT )
	{
		mlx_mouse_move(data->mlx_win, data->mouse_x, HEIGHT / 2);
		data->mouse_y = HEIGHT / 2;
	}
	data->prev_mouse_x = data->mouse_x;
	data->prev_mouse_y = data->mouse_y;
	
	mlx_mouse_get_pos(data->mlx_win, &data->mouse_x, &data->mouse_y);
	move_angle_x = data->prev_mouse_x - data->mouse_x;
	move_angle_y = data->prev_mouse_y - data->mouse_y;
	if(move_angle_x > 10)
		move_angle_x = 10;
	if(move_angle_x < -10)
		move_angle_x = -10;
	move_angle_x *= 0.01f;
	move_angle_y *= 6;
	if(move_angle_x > 0)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(-move_angle_x) - \
			data->map->play.dir_y * sin(-move_angle_x);
		data->map->play.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->play.dir_y * cos(-move_angle_x);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-move_angle_x) - \
			data->map->cam.pl_y * sin(-move_angle_x);
		data->map->cam.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->cam.pl_y * cos(-move_angle_x);
		data->map->play.a += -move_angle_x;
	}
	else if(move_angle_x < 0)
	{
		data->map->play.dir_x = data->map->play.dir_x * cos(-move_angle_x) - \
			data->map->play.dir_y * sin(-move_angle_x);
		data->map->play.dir_y = dir_x * sin(-move_angle_x) + \
			data->map->play.dir_y * cos(-move_angle_x);
		data->map->cam.pl_x = data->map->cam.pl_x * cos(-move_angle_x) - \
			data->map->cam.pl_y * sin(-move_angle_x);
		data->map->cam.pl_y = plane_x * sin(-move_angle_x) + \
			data->map->cam.pl_y * cos(-move_angle_x);
		data->map->play.a += -move_angle_x;
	}
	if(move_angle_y > 0)
		data->map->cam.vertilcal_pos += move_angle_y;
	else if(move_angle_y < 0)
		data->map->cam.vertilcal_pos += move_angle_y;
}

int	render_next_frame(t_data_mlx *data)
{
	int			img_h;
	int			img_w;
	static int	i_space;

	if (data->map->play.f_map)
	{
		draw_fvp(data);
		draw_objects(data);
		if (data->map->play.f_minimap)
			draw_minimap(data);
	}
	if (!data->map->play.f_map)
	{	
		++i_space;
		if (i_space > 39)
			i_space = 0;
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, \
			data->image.mm_space[i_space], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, \
			WIDTH / 2 - data->map->width * TEXSIZE / 2, \
			HEIGHT / 2 - data->map->height * TEXSIZE / 2);
		mlx_destroy_image(data->mlx, data->img);
	}
	mouse_move(data);
	key_h(data);
	mlx_mouse_hide();
	return (0);
}

void	init_images(t_data_mlx *data)
{
	int		i;
	int		j;
	char	xpm_path[1024];
	char	*space_dir;
	char	*among_dir;
	char	*comp_dir;
	char	*img_num;
	int		img_h;
	int		img_w;

	data->am_s = malloc(sizeof(t_spr));
	if (!data->am_s)
		error_end(3); // move it && save pointer
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
		data->image.mm_space[i] = \
			mlx_xpm_file_to_image(data->mlx, xpm_path, &img_h, &img_w);
	}
	// init animated among dead
	j = 0;
	i = -1;
	among_dir = "./textures/among/0";
	while (++i < SPR_COSTUME)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, among_dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);
		// printf ("%s\n", xpm_path_among);
		data->am_s->spr_img[j].costumes[i].img = \
			mlx_xpm_file_to_image(data->mlx, xpm_path, &data->am_s->spr_img[j].costumes[i].img_h, &data->am_s->spr_img[j].costumes[i].img_w);
		data->am_s->spr_img[j].costumes[i].addr = mlx_get_data_addr(data->am_s->spr_img[j].costumes[i].img, &data->am_s->spr_img[j].costumes[i].bits_per_pixel, \
			&data->am_s->spr_img[j].costumes[i].line_length, &data->am_s->spr_img[j].costumes[i].endian);
	}
	while (++j < SPR_NUM)
	{
		i = -1;
		while (++i < SPR_COSTUME)
		{
			data->am_s->spr_img[j].costumes[i].img = data->am_s->spr_img[0].costumes[i].img;
			data->am_s->spr_img[j].costumes[i].addr = data->am_s->spr_img[0].costumes[i].addr;
			data->am_s->spr_img[j].costumes[i].img_h = data->am_s->spr_img[0].costumes[i].img_h;
			data->am_s->spr_img[j].costumes[i].img_w = data->am_s->spr_img[0].costumes[i].img_w;
			data->am_s->spr_img[j].costumes[i].bits_per_pixel = data->am_s->spr_img[0].costumes[i].bits_per_pixel;
			data->am_s->spr_img[j].costumes[i].line_length = data->am_s->spr_img[0].costumes[i].line_length;
			data->am_s->spr_img[j].costumes[i].endian = data->am_s->spr_img[0].costumes[i].endian;
		}
	}
	// init rickroll
	i = -1;
	comp_dir = "./textures/rick/";
	while (++i < COMP_COSTUME)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path, comp_dir, 1023);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path, img_num, 1023);
		free(img_num);
		ft_strlcat(xpm_path, ".xpm", 1023);	
		printf ("%s\n", xpm_path);
		data->am_s->comp_img.costumes[i].img = \
			mlx_xpm_file_to_image(data->mlx, xpm_path, &data->am_s->comp_img.costumes[i].img_h, &data->am_s->comp_img.costumes[i].img_w);
		data->am_s->comp_img.costumes[i].addr = mlx_get_data_addr(data->am_s->comp_img.costumes[i].img, &data->am_s->comp_img.costumes[i].bits_per_pixel, \
			&data->am_s->comp_img.costumes[i].line_length, &data->am_s->comp_img.costumes[i].endian);
	}
	//init weapon texture
	data->weapon.img = mlx_xpm_file_to_image(data->mlx, "./textures/blaster1.xpm", \
		&data->weapon.img_w, &data->weapon.img_h);
	printf("w : %d h : %d\n", data->weapon.img_w, data->weapon.img_h);
	data->weapon.addr = mlx_get_data_addr(data->weapon.img, &data->weapon.bits_per_pixel, \
		&data->weapon.line_length, &data->weapon.endian);
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
	//init compas
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

static void	init_sprite_data(t_data_mlx *data)
{
	data->am_s->spr_img[0].x = 22.5;
	data->am_s->spr_img[0].y = 4.5;
	data->am_s->spr_img[1].x = 38.5;
	data->am_s->spr_img[1].y = 10.5;
	data->am_s->spr_img[2].x = 26.5;
	data->am_s->spr_img[2].y = 15.5;
	data->am_s->spr_img[3].y = 23.5;
	data->am_s->spr_img[3].x = 23.5;
	data->am_s->spr_img[0].dead = 0;
	data->am_s->spr_img[0].shot = 0;
	data->am_s->spr_img[1].dead = 0;
	data->am_s->spr_img[1].shot = 0;
	data->am_s->spr_img[2].dead = 0;
	data->am_s->spr_img[2].shot = 0;
	data->am_s->spr_img[3].dead = 0;
	data->am_s->spr_img[3].shot = 0;
	data->am_s->comp_img.x = 11.5;
	data->am_s->comp_img.y = 10.5;
	data->am_s->comp_img.shot = 0;
}

int	draw(t_info *map)
{
	t_data_mlx	data;
	int i;

	i = 0;
	map->play.f_map = 0;
	map->play.f_minimap = 0;
	data.map = map;
	data.map->cam.vertilcal_pos = 0;
	while(i < MAX_KEYS_NUM)
		data.keycode[i++] = UNPRESS; //init unpress keys
	data.mouse_x = WIDTH / 2;
	data.mouse_y = HEIGHT / 2;
	// printf("here x = %f y = %f\n", map->play.x, map->play.y);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_mouse_move(data.mlx_win, WIDTH / 2, HEIGHT / 2);
	init_images(&data);
	init_sprite_data(&data);
	// render_next_frame(&data);
	mlx_hook(data.mlx_win, 2, 0, &key_press, &data);
	mlx_hook(data.mlx_win, 3, 0, &key_unpress, &data);
	mlx_mouse_hook(data.mlx_win, &ft_mouse, &data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	
	// mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
