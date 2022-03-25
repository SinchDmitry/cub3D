/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:57:59 by aarchiba          #+#    #+#             */
/*   Updated: 2022/03/25 20:11:31 by aarchiba         ###   ########.fr       */
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

typedef struct s_play
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
	int		f_minimap;
	int		side_for_move;
}	t_play;

typedef struct s_cam
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
	int		vertilcal_pos; // up and down cam
}	t_cam;

typedef struct s_images
{
	void	*mm_space[40];
	void	*compas;
}	t_images;

typedef struct s_slot
{
	char	sym;
}	t_slot;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_texture
{
	char	*east;
	char	*west;
	char	*north;
	char	*south;
}	t_texture;

typedef struct s_info
{
	int			max_i;
	int			max_j;
	int			fd;
	int			width;
	int			height;
	t_rgb		*sky;
	t_rgb		*floor;
	t_slot		**mapa;
	t_play		play;
	t_cam		cam;
	t_texture	*texture;
}	t_info;

int		draw(t_info *map);
t_info	*parser(int argc, char **argv, int fd);

#endif
