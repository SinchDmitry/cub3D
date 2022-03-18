/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:19:11 by utygett           #+#    #+#             */
/*   Updated: 2022/03/18 20:00:31 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

void	init_cam(t_data_mlx *data, int x)
{
	data->map->cam.cam = 2 * x / (float)WIDTH - 1;
	data->map->cam.cam_dir_x = data->map->play.dir_x + \
		data->map->cam.pl_x * data->map->cam.cam;
	data->map->cam.cam_dir_y = data->map->play.dir_y + \
		data->map->cam.pl_y * data->map->cam.cam;
	data->map->cam.delta_dir_x = fabsf(1 / data->map->cam.cam_dir_x);
	data->map->cam.delta_dir_y = fabsf(1 / data->map->cam.cam_dir_y);
	data->map->cam.ray_pos_x = data->map->play.x;
	data->map->cam.ray_pos_y = data->map->play.y;
}

static void	init_cam_move(t_data_mlx *data)
{
	if (data->map->cam.cam_dir_x < 0)
	{
		data->map->cam.step_x = -1;
		data->map->cam.side_dist_x = (data->map->play.x - \
			data->map->cam.ray_pos_x) * data->map->cam.delta_dir_x;
	}
	else
	{
		data->map->cam.step_x = 1;
		data->map->cam.side_dist_x = (data->map->cam.ray_pos_x + 1.0 - \
			data->map->play.x) * data->map->cam.delta_dir_x;
	}
	if (data->map->cam.cam_dir_y < 0)
	{
		data->map->cam.step_y = -1;
		data->map->cam.side_dist_y = (data->map->play.y - \
			data->map->cam.ray_pos_y) * data->map->cam.delta_dir_y;
	}
	else
	{
		data->map->cam.step_y = 1;
		data->map->cam.side_dist_y = (data->map->cam.ray_pos_y + 1.0 - \
			data->map->play.y) * data->map->cam.delta_dir_y;
	}
}

static void	ray_calc(t_data_mlx *data)
{
	if (data->map->cam.side_dist_x < data->map->cam.side_dist_y)
	{
		data->map->cam.side_dist_x += data->map->cam.delta_dir_x;
		data->map->cam.ray_pos_x += data->map->cam.step_x;
		data->map->cam.wall_dir = 0;
	}
	else
	{
		data->map->cam.side_dist_y += data->map->cam.delta_dir_y;
		data->map->cam.ray_pos_y += data->map->cam.step_y;
		data->map->cam.wall_dir = 1;
	}
}

void	ray_play(t_data_mlx *data, int flag)
{
	int			x;
	int			i;

	x = -1;
	while (++x < WIDTH)
	{
		init_cam(data, x);
		init_cam_move(data);
		i = -1;
		while (++i < VIEW_RANGE)
		{
			ray_calc(data);
			if (data->map->mapa[data->map->cam.ray_pos_y] \
				[data->map->cam.ray_pos_x].sym != '0')
				break ;
		}
		if (data->map->cam.wall_dir)
			data->sector[x] = (data->map->cam.side_dist_y - \
				data->map->cam.delta_dir_y);
		else
			data->sector[x] = (data->map->cam.side_dist_x - \
				data->map->cam.delta_dir_x);
		////////////////////// draw
		int lineHeight = (int)(HEIGHT / data->sector[x]);
		 // up and down cam
		float	abc = 2;
		int drawStart = -lineHeight / abc + HEIGHT / abc + data->map->cam.vertilcal_pos;
		
     	if(drawStart < 0)
			drawStart = 0;

		int drawEnd = lineHeight / abc + HEIGHT / abc + data->map->cam.vertilcal_pos;
		
    	if(drawEnd >= HEIGHT) 
			drawEnd = HEIGHT - 1;
			
		// x cordinate for wall side or front
		double wallX;
		if(!data->map->cam.wall_dir)
			wallX = data->map->play.y + data->sector[x] * data->map->cam.cam_dir_y;
		else
			wallX = data->map->play.x + data->sector[x] * data->map->cam.cam_dir_x;
		wallX = wallX - floor(wallX);
		//x coordinate on the texture
		char sym;
		sym = 0;
		if (!data->map->cam.wall_dir)
		{
			if (data->map->cam.step_x == -1)
				sym = 0;
			else
				sym = 1;
		}
		else
		{
			if (data->map->cam.step_y == -1)
				sym = 2;
			else
				sym = 3;
		}

		int texX = (int)(wallX * (double)data->wall[sym].img_w);
		

			texX = data->wall[sym].img_w - texX - 1;
		double step = 1.0 * data->wall[sym].img_w / lineHeight;
		double texPos = (drawStart - data->map->cam.vertilcal_pos - HEIGHT / 2 + lineHeight / 2) * step;
		unsigned int col;
		// side of wall
		//draw vertical line
     	for(int y = drawStart; y < drawEnd; y++)
     	{
			int texY = (int)texPos & (data->wall[sym].img_h - 1);
       		texPos += step;
			col = my_mlx_get_pixel(data, texX, texY, sym);
			// if(data->map->cam.wall_dir == 1) // make shadow
			// 	col = (col >> 1) & 8355711;
		
			if (!data->map->cam.wall_dir)
			{
				// if (data->map->cam.step_x == -1)
				// 	col = (col >> 1) & 8355711;
			}
			else
			{
				// if (data->map->cam.step_y == -1)
					// col = (col >> 1) & 8355711;
				// else
					// col = (col >> 1) & 8355711;
			}

			my_mlx_pixel_put(data, x, y, col);
		}
	}
}