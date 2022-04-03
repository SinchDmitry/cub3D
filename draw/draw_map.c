/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 15:04:49 by utygett           #+#    #+#             */
/*   Updated: 2022/04/03 16:09:20 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

/* "./textures/player_arrow.cub" */
int	**init_play_arrow(char *arrow)
{
	int		i;
	int		j;
	int		fd;
	int		**img;
	char	**file;

	fd = open(arrow, O_RDONLY);
	file = get_line_file(fd);
	i = -1;
	img = ft_calloc_error_end(sizeof(int *), 10, P_FRONT);
	while (++i < 10)
		img[i] = ft_calloc_error_end(sizeof(int), 10, P_FRONT);
	i = -1;
	while (++i < 10)
	{
		j = -1;
		while (++j < 10)
			img[i][j] = (int)file[i][j] - 48;
	}
	return (img);
}

void	draw_play(t_play *play, t_data_mlx *data)
{
	float	x;
	float	y;
	float	point_x;
	float	point_y;

	play->pl_arrow = init_play_arrow("./textures/player_arrow.cub");
	play->x_textu = play->x * data->map->texture_size;
	play->y_textu = play->y * data->map->texture_size;
	x = play->x_textu -1;
	while (++x < play->x_textu + 10)
	{
		y = play->y_textu - 1;
		while (++y < play->y_textu + 10)
		{
			point_x = (x - play->x_textu - 5) * cos(data->map->play.a) - \
				(y - play->y_textu - 5) * sin(data->map->play.a);
			point_y = (x - play->x_textu - 5) * sin(data->map->play.a) + \
				(y - play->y_textu - 5) * cos(data->map->play.a);
			if (play->pl_arrow[(int)(x - play->x_textu)] \
				[(int)(y - play->y_textu)] == 1)
				my_mlx_pixel_put(data, point_x + play->x_textu, point_y + \
					play->y_textu, GREEN_COL);
		}
	}
}

void	draw_square(int x, int y, t_data_mlx *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (x + i < x + data->map->texture_size)
	{
		j = 0;
		while (y + j < y + data->map->texture_size)
		{
			my_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}	
}

void	draw_field(int x, int y, t_data_mlx *data)
{
	t_spr_tex	*tmp_img;

	if (data->map->mapa[x][y].sym == '1')
		draw_square(y * data->map->texture_size, x * \
			data->map->texture_size, data, WALLCOL);
	else if (data->map->mapa[x][y].sym == '0')
		draw_square(y * data->map->texture_size, x * \
			data->map->texture_size, data, FLOORCOL);
	if (data->map->mapa[x][y].door == 1)
		draw_square(y * data->map->texture_size, x * \
			data->map->texture_size, data, BLUE_COL);
	tmp_img = data->am_s->spr_img;
	while (tmp_img)
	{	
		if (!tmp_img->dead)
			draw_square((int)tmp_img->x * data->map->texture_size, \
				(int)tmp_img->y * data->map->texture_size, \
				data, RED_COL);
		else
			draw_square((int)tmp_img->x * data->map->texture_size, \
				(int)tmp_img->y * data->map->texture_size, \
				data, GREEN_COL);
		tmp_img = tmp_img->next;
	}
}

void	draw_map(t_data_mlx *data)
{
	int		i;
	int		j;

	i = 0;
	draw_invis_background(data, WIDTH, HEIGHT);
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
	draw_play(&data->map->play, data);
}
