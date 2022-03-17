/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:43:08 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/17 15:58:04 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

// void	init_sprite(t_spr *am_s)
// {
// 	am_s = malloc(sizeof(t_spr) * AM_SPRITE_NUM);
// 	if (!am_s)
// 		error_end(3);
// 	am_s[0].x = 22.5;
// 	am_s[0].y = 4.5;
// 	am_s[0].id = 1;
// 	am_s[1].x = 11.5;
// 	am_s[1].y = 10.5;
// 	am_s[1].id = 2;
// 	am_s[2].x = 26.5;
// 	am_s[2].y = 15.5;
// 	am_s[2].id = 3;
// 	am_s[3].x = 23.5;
// 	am_s[3].y = 23.5;
// 	am_s[3].id = 4;
// }

// void	init_sort_dist(t_data_mlx *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < AM_SPRITE_NUM)
// 	{
// 		data->am_s[i].dist = ((data->map->player.x - data->am_s[i].x) * \
// 			(data->map->player.x - data->am_s[i].x) + (data->map->player.y - \
// 			data->am_s[i].y) * (data->map->player.y - data->am_s[i].y));
// 	}
	
// }

void	draw_sprite(t_data_mlx *data)
{
	float	inv;
	float	t_x;
	float	t_y;
	int		pos_spr_x;
	int		h_spr;
	int		w_spr;
	int		dr_st_x;
	int		dr_st_y;
	int		dr_f_x;
	int		dr_f_y;
	int		i;
	int		j;
	int 	tex_x;
	int 	tex_y;
	int		d;

	data->am_s->x = 22.5;
	data->am_s->y = 4.5;
	data->am_s->id = 1;
	
	data->am_s->x_ray = data->am_s->x - data->map->player.x;
	data->am_s->y_ray = data->am_s->y - data->map->player.y;
	inv = 1.0 / (data->map->camera.pl_x * data->map->player.dir_y - \
		data->map->player.dir_x * data->map->camera.pl_y);
	t_x = inv * (data->map->player.dir_y * data->am_s->x_ray - \
		data->map->player.dir_x * data->am_s->y_ray);
	t_y = inv * (-data->map->camera.pl_y * data->am_s->x_ray + \
		data->map->camera.pl_x * data->am_s->y_ray);
	pos_spr_x = (int)((WIDTH / 2) * (1 + t_x / t_y));
	
	h_spr = abs((int)(HEIGHT / t_y));
	dr_st_y = -(h_spr / 2) + HEIGHT / 2; // - data->map->camera.vertilcal_pos;
	if (dr_st_y < 0)
		dr_st_y = 0;
	dr_f_y = h_spr / 2 + HEIGHT / 2; // - data->map->camera.vertilcal_pos;
	if (dr_f_y > HEIGHT)
		dr_f_y = HEIGHT - 1;
		
	w_spr = abs((int)(HEIGHT / t_y)); 
	dr_st_x = -w_spr / 2 + pos_spr_x;
	if (dr_st_x < 0)
		dr_st_x = 0;
	dr_f_x = w_spr / 2 + pos_spr_x;
	if (dr_f_x >= WIDTH)
		dr_f_x = WIDTH - 1;
	// i = (dr_st_x + dr_f_x) / 2 - 1;
	i = dr_st_x - 1;
	while (++i < dr_f_x)
	{
		tex_x = ((int)(256 * (i - (-w_spr / 2 + pos_spr_x)) * \
			data->am_s->spr_img.img_w / w_spr) / 256);
		if (t_y > 0 && i > 0 && i < WIDTH && t_y < data->sector[i]) // ?
		{
			// j = (dr_st_y + dr_f_y) / 2 - 1;
			j = dr_st_y - 1;
			while (++j < dr_f_y)
			{
				d = j * 256 - HEIGHT * 128 + h_spr * 128;
				tex_y = (((d * data->am_s->spr_img.img_h) / h_spr) / 256);
				my_mlx_pixel_put(data, i , j + data->map->camera.vertilcal_pos, my_mlx_get_pixel(data, tex_x, tex_y, 4));
          		// if((color & 0x00FFFFFF) != 0) 
				// 	buffer[j][i] = color; // buffer ?
			}
		}
	}
	
	// for(int stripe = drawStartX; stripe < drawEndX; stripe++)
    //   {
    //     int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
    //     //the conditions in the if are:
    //     //1) it's in front of camera plane so you don't see things behind you
    //     //2) it's on the screen (left)
    //     //3) it's on the screen (right)
    //     //4) ZBuffer, with perpendicular distance
    //     if(transformY > 0 && stripe > 0 && stripe < w && transformY < ZBuffer[stripe])
    //     for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
    //     {
    //       int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
    //       int texY = ((d * texHeight) / spriteHeight) / 256;
    //       Uint32 color = texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
    //       if((color & 0x00FFFFFF) != 0) buffer[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
    //     }
    //   }
}

void	draw_objects(t_data_mlx *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, \
		&data->line_length, &data->endian);
	draw_invis_background(data, WIDTH, HEIGHT);
	draw_sprite(data);
	draw_aim(data);
	if (data->mouse_code[MOUSE_RIGHT_KEY] == PRESS)
		attack_weapon(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	put_weapon_image(data);
	mlx_destroy_image(data->mlx, data->img);
}
