/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/12 21:56:25 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	init_camera(t_data_mlx *data, int x)
{
	data->map->camera.cam = 2 * x / (float)WIDTH - 1;
	data->map->camera.cam_dir_x = data->map->player.dir_x + \
		data->map->camera.pl_x * data->map->camera.cam;
	data->map->camera.cam_dir_y = data->map->player.dir_y + \
		data->map->camera.pl_y * data->map->camera.cam;
	data->map->camera.delta_dir_x = fabsf(1 / data->map->camera.cam_dir_x);
	data->map->camera.delta_dir_y = fabsf(1 / data->map->camera.cam_dir_y);
	data->map->camera.ray_pos_x = data->map->player.x;
	data->map->camera.ray_pos_y = data->map->player.y;
}

static void	init_camera_move(t_data_mlx *data)
{
	if (data->map->camera.cam_dir_x < 0)
	{
		data->map->camera.step_x = -1;
		data->map->camera.side_dist_x = (data->map->player.x - \
			data->map->camera.ray_pos_x) * data->map->camera.delta_dir_x;
	}
	else
	{
		data->map->camera.step_x = 1;
		data->map->camera.side_dist_x = (data->map->camera.ray_pos_x + 1.0 - \
			data->map->player.x) * data->map->camera.delta_dir_x;
	}
	if (data->map->camera.cam_dir_y < 0)
	{
		data->map->camera.step_y = -1;
		data->map->camera.side_dist_y = (data->map->player.y - \
			data->map->camera.ray_pos_y) * data->map->camera.delta_dir_y;
	}
	else
	{
		data->map->camera.step_y = 1;
		data->map->camera.side_dist_y = (data->map->camera.ray_pos_y + 1.0 - \
			data->map->player.y) * data->map->camera.delta_dir_y;
	}
}

static void	ray_calc(t_data_mlx *data)
{
	if (data->map->camera.side_dist_x < data->map->camera.side_dist_y)
	{
		data->map->camera.side_dist_x += data->map->camera.delta_dir_x;
		data->map->camera.ray_pos_x += data->map->camera.step_x;
		data->map->camera.wall_dir = 0;
	}
	else
	{
		data->map->camera.side_dist_y += data->map->camera.delta_dir_y;
		data->map->camera.ray_pos_y += data->map->camera.step_y;
		data->map->camera.wall_dir = 1;
	}
}

// void	side_calc(t_data_mlx *data, t_tex *last)
// {
// 	if (!data->map->camera.wall_dir)
// 	{
// 		if (data->map->camera.step_x == -1)
// 			last->side = 'W';
// 		else
// 			last->side = 'E';
// 	}
// 	else
// 	{
// 		if (data->map->camera.step_y == -1)
// 			last->side = 'N';
// 		else
// 			last->side = 'S';
// 	}
// }

// void	add_back(t_data_mlx *data, t_tex **lst, t_tex_data *xyj)
// {
// 	t_tex	*last;
// 	t_tex	*tmp;

// 	tmp = *lst;
// 	last = malloc (sizeof(t_tex));
// 	side_calc(data, last);
// 	last->next = NULL;
// 	last->pixel_x = xyj->p_x;
// 	last->pixel_y = xyj->p_y;
// 	last->ray_counter = xyj->j;
// 	if (!(*lst))
// 		*lst = last;
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = last;
// 	}
// }

void	ray_player(t_data_mlx *data, int flag)
{
	int			x;
	int			i;
	t_tex_data	xyj;

	x = -1;
	xyj.j = 0;
	data->map->texture->ture = NULL;
	xyj.p_y = -1;
	xyj.p_x = -1;
	while (++x < WIDTH)
	{
		init_camera(data, x);
		init_camera_move(data);
		i = -1;
		while (++i < VIEW_RANGE)
		{
			ray_calc(data);
			if (data->map->mapa[data->map->camera.ray_pos_y] \
				[data->map->camera.ray_pos_x].sym != '0')
				break ;
		}
		if (data->map->camera.ray_pos_y != xyj.p_y \
		|| data->map->camera.ray_pos_x != xyj.p_x)
		{
			if (xyj.p_y != -1 && xyj.p_x != -1)
			{
				// add_back(data, &data->map->texture->ture, &xyj);
				xyj.j = 0;
			}
			xyj.p_x = data->map->camera.ray_pos_x;
			xyj.p_y = data->map->camera.ray_pos_y;
		}
		xyj.j++;
		if (data->map->camera.wall_dir)
			data->sector[x] = (data->map->camera.side_dist_y - \
				data->map->camera.delta_dir_y);
		else
			data->sector[x] = (data->map->camera.side_dist_x - \
				data->map->camera.delta_dir_x);

		////////////////////// draw
		int lineHeight = (int)(HEIGHT / data->sector[x]);
		 // up and down camera
		int drawStart = -lineHeight / 2 + HEIGHT / 2 + data->map->camera.vertilcal_pos;
		
     	if(drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / 2 + HEIGHT / 2 + data->map->camera.vertilcal_pos;
		
    	if(drawEnd >= HEIGHT) 
			drawEnd = HEIGHT - 1;
			
		// x cordinate for wall side or front
		double wallX;
		if(!data->map->camera.wall_dir)
			wallX = data->map->player.y + data->sector[x] * data->map->camera.cam_dir_y;
		else
			wallX = data->map->player.x + data->sector[x] * data->map->camera.cam_dir_x;
		wallX = wallX - floor(wallX);
		//x coordinate on the texture
		int texX = (int)(wallX * (double)256);
		
		// if(data->map->camera.wall_dir == 0 && data->map->camera.cam_dir_x > 0)
		// 	texX = 256 - texX - 1;
		// if(data->map->camera.wall_dir == 1 && data->map->camera.cam_dir_y > 0) //for what that need?
			texX = 256 - texX - 1;
		double step = 1.0 * 256 / lineHeight;
		double texPos = (drawStart - data->map->camera.vertilcal_pos - HEIGHT / 2 + lineHeight / 2) * step;
		unsigned int col;
		// side of wall
		char sym;
		sym = 'W';
		if (!data->map->camera.wall_dir)
		{
			
			if (data->map->camera.step_x == -1)
				sym = 'W';
			else
				sym = 'S';
		}
		else
		{
			if (data->map->camera.step_y == -1)
				sym = 'E';
			else
				sym = 'N';
		}
		//draw vertical line
     	for(int y = drawStart; y < drawEnd; y++)
     	{
			int texY = (int)texPos & (256 - 1);
       		texPos += step;
			col = my_mlx_get_pixel(data, texX, texY, sym);
			// if(data->map->camera.wall_dir == 1) // make shadow
			// 	col = (col >> 1) & 8355711;
		
			if (!data->map->camera.wall_dir)
			{
				// if (data->map->camera.step_x == -1)
				// 	col = (col >> 1) & 8355711;
			}
			else
			{
				// if (data->map->camera.step_y == -1)
					// col = (col >> 1) & 8355711;
				// else
					// col = (col >> 1) & 8355711;
			}

			my_mlx_pixel_put(data, x, y, col);
		}
		// draw_ray_cast(data, x, HEIGHT / data->sector[x], texX);
	}
	// printf("y : %f x : %f\n", data->map->player.y, data->map->player.x );
	// add_back(data, &data->map->texture->ture, &xyj);
	// while (data->map->texture->ture)
	// {
	// 	printf("x : %5d | y : %5d | num : %5d | side : %c\n", data->map->texture->ture->pixel_x, data->map->texture->ture->pixel_y, data->map->texture->ture->ray_counter, data->map->texture->ture->side);
	// 	data->map->texture->ture = data->map->texture->ture->next;
	// }
	// printf("<<<<<<<<<>>>>>>>>>>\n");
	// x = -1;
	// int num = data->map->texture->ture->ray_counter;
	// int j = 0;
	// 	printf("x : %5d | y : %5d | num : %5d | side : %c\n", data->map->texture->ture->pixel_x, data->map->texture->ture->pixel_y, data->map->texture->ture->ray_counter, data->map->texture->ture->side);

	
	// while (++x < WIDTH)
	// {
	// 		double wallX;
	// 	if(data->map->camera.wall_dir)
	// 		wallX = data->map->camera.ray_pos_y + data->sector[x] * data->map->camera.cam_dir_y;
	// 	else
	// 		wallX = data->map->camera.ray_pos_x + data->sector[x] * data->map->camera.cam_dir_x;
	// 	wallX -= floor((wallX));
	// 	if(x > num && data->map->texture->ture)
	// 	{
	// 		printf("x : %5d | y : %5d | num : %5d | side : %c\n", data->map->texture->ture->pixel_x, data->map->texture->ture->pixel_y, data->map->texture->ture->ray_counter, data->map->texture->ture->side);
	// 		data->map->texture->ture = data->map->texture->ture->next;
	// 		num += data->map->texture->ture->ray_counter;
	// 		j = 0;
	// 	}
	// 	j++;
	// 	printf("x :%d wallx : %f\n",x, wallX);
	// 	draw_ray_cast(data, x, HEIGHT / data->sector[x], step_counter_texture(1 / 256, wallX));
	// 	// draw_ray_cast(data, x, HEIGHT / data->sector[x], j);
	// }
}

/*
void	ray_player(t_data_mlx *data, int flag)
{
	int		x;
	int		i;
	t_vls	xy;

	x = -1;
	while (++x < WIDTH)
	{
		init_camera(data, x);
		init_camera_move(data);
		i = -1;
		while (++i < VIEW_RANGE)
		{
			ray_calc(data);
			if (data->map->mapa[data->map->camera.ray_pos_y] \
				[data->map->camera.ray_pos_x].sym != '0')
				break ;
		}	
		if (!flag)
		{
			xy.x1 = data->map->player.x * TEXSIZE;
			xy.y1 = data->map->player.y * TEXSIZE;
			xy.x2 = ((data->map->camera.ray_pos_x)) * TEXSIZE;
			if (data->map->camera.ray_pos_x <= data->map->player.x)
				xy.x2 = ((data->map->camera.ray_pos_x + 1)) * TEXSIZE;
			xy.y2 = ((data->map->camera.ray_pos_y)) * TEXSIZE;
			if (data->map->camera.ray_pos_y <= data->map->player.y)
				xy.y2 = ((data->map->camera.ray_pos_y + 1)) * TEXSIZE;
			
			// xy.x2 = ((data->map->camera.ray_pos_x) + (data->map->camera.ray_pos_x - data->map->camera.side_dist_x)) * TEXSIZE;
			// xy.y2 = ((data->map->camera.ray_pos_y) + (data->map->camera.ray_pos_x - data->map->camera.side_dist_y)) * TEXSIZE;
			
			// if (data->map->camera.cam_dir_x)
			// 	xy.x2 = (data->map->camera.side_dist_x) * TEXSIZE;
			// if (data->map->camera.cam_dir_y)
			// 	xy.x2 = (data->map->camera.side_dist_y) * TEXSIZE;

			draw_line(data, xy);
		}
		if (data->map->camera.wall_dir)
			data->sector = (data->map->camera.side_dist_y - \
				data->map->camera.delta_dir_y);
		else
			data->sector = (data->map->camera.side_dist_x - \
				data->map->camera.delta_dir_x);
		if (flag)
			draw_ray_cast(data, x, HEIGHT / data->sector, \
				step_counter_texture(0.00390625f, 0));
	}
}
*/