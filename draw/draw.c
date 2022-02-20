/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/02/20 18:25:40 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color)
{
	char	*dst;
	if(x < WIDTH && x >= 0 && y < HEIGHT && y >= 0){

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	}
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

void	line_math(t_data_mlx *data, float rad)
{
	float	c;
	float	ray_x;
	float	ray_y;

	c = 0;
	while (c < VIEW_RANGE)
	{
		ray_x = data->map->player.x + c * cos(data->map->player.a + rad);
		ray_y = data->map->player.y + c * sin(data->map->player.a + rad);
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
	int	i;
	int	j;

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
	float a = - 0.75f;
	while (a < 0.75f)
	{
		line_math(data, a);
		a = a + 0.03f;
	}
	
}

void	ft_mlx(t_data_mlx *data)
{
	
	// draw minimap
	int img_h;
	int img_w;
	data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	draw_map_with_move(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx,data->img);
	// draw map
	if(data->map->player.f_map){
		

		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx,data->img);
	}
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
	if(keycode == MAP_KEY){
		if(data->map->player.f_map)
		{
			mlx_clear_window(data->mlx,data->mlx_win);
			data->map->player.f_map  = 0;
		}
		else
			data->map->player.f_map  = 1;
	}
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
	// ft_mlx(data);
	return (0);
}

void	draw_ray_catsing(t_data_mlx *data, float x, float height)
{
	float i;
	i = 0 - height / 2;
	while (i < height / 2)
	{
		my_mlx_pixel_put(data, x, HEIGHT / 2 + i, WHITE_COL);
		++i;
	}
}


void draw_fvp(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	float i = 500;
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx,data->img);
}

int	render_next_frame(t_data_mlx *data){
	int img_h;
	int img_w;
	static int i;
	if(data->map->player.f_map)
	{
		
		data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
		data->img = mlx_xpm_file_to_image(data->mlx, "./textures/backgroundmap.xpm", &img_h, &img_w);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
			&data->line_length, &data->endian);
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx,data->img);
	}
	if(!data->map->player.f_map)
	{
		++i;
		if(i > 39)
			i = 0;
		
		draw_fvp(data);
		data->img = mlx_new_image(data->mlx, MINIMAPWIDTH, MINIMAPHEIGHT);
		// data->image.mm_space[i] = mlx_xpm_file_to_image(data->mlx, xpm_path, &img_h, &img_w);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, 
			&data->line_length, &data->endian);
		draw_map_with_move(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->image.mm_space[i], 0, 0);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
		mlx_destroy_image(data->mlx,data->img);
	}
	// draw map
	
	return(0);
}

void init_images(t_data_mlx *data)
{
	int	i;
	char	xpm_path[1024];
	char *space_dir = "./textures/space_fly/space2/space_fly";
	char *img_num;
	int img_h;
	int img_w;
	
	i = 0;
	while( i < 40)
	{
		xpm_path[0] = '\0';
		ft_strlcat(xpm_path,space_dir, 1024);
		img_num = ft_itoa(i);
		ft_strlcat(xpm_path,img_num, 1024);
		free(img_num);
		ft_strlcat(xpm_path,".xpm", 1024);
		data->image.mm_space[i] = mlx_xpm_file_to_image(data->mlx, xpm_path, &img_h, &img_w);
		i++;
	}
}

int	draw(t_info *map)
{
	t_data_mlx data;
	map->player.f_map = 0;
	data.map = map;
	printf("here x = %f y = %f\n",map->player.x, map->player.y);
	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
	init_images(&data);
	ft_mlx(&data);
	mlx_loop_hook(data.mlx, render_next_frame, &data);
	mlx_hook(data.mlx_win, 02, (1L << 0), &key_h, &data);
	mlx_loop(data.mlx);
	return (0);
}
