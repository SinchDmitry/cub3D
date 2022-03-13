/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:57:59 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/13 13:04:07 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "math.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
// # include "parser/parser.h"
// # include "draw/draw.h"
// # include <mlx.h>
# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define P_BACK 2
# define P_FRONT 1

typedef struct s_player
{
	float	x;
	float	y;
	float	a;
	float	dir;
	float	dir_x;
	float	dir_y;
	int		f_map;
	float	x_textu;
	float	y_textu;
	// char	dir;
	int		f_minimap;
}	t_player;

typedef struct s_camera
{
	float	x;
	float	y;
	float	cam;
	float	pl_x;
	float	pl_y;
	int		step_x;
	int		step_y;
	float	wall_dir;
	float	cam_dir_x;
	float	cam_dir_y;
	int		ray_pos_x;
	int		ray_pos_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dir_x;
	float	delta_dir_y;
	float	correct_dist;
	int		vertilcal_pos; // up and down camera
}	t_camera;

typedef struct s_images
{
	void	*mm_space[40];
	void	*compas[4];
}	t_images;

typedef struct s_data
{
	char	sym;
}	t_data;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_tex_data
{
	int		p_x;
	int		p_y;
	int		j;
}	t_tex_data;

typedef struct s_tex
{
	char			side;
	struct s_tex	*next;
	int				pixel_x;
	int				pixel_y;
	int				ray_counter;
}	t_tex;

typedef struct s_texture
{
	char	*east;
	char	*west;
	char	*north;
	char	*south;
	t_tex	*ture;
}	t_texture;

typedef struct s_info
{
	t_data		**mapa;
	int			fd;
	int			width;
	int			height;
	t_player	player;
	t_camera	camera;
	t_rgb		*sky;
	t_rgb		*floor;
	t_texture	*texture;
}	t_info;

int		draw(t_info *map);
t_info	*parser(int argc, char **argv, int fd);

#endif
