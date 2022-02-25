/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:57:59 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/24 21:48:37 by utygett          ###   ########.fr       */
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
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define P_BACK 2
# define P_FRONT 1

typedef struct	s_player {
	float	x;
	float	y;
	float	a;
	float	x_textu;
	float	y_textu;
	char	dir;
	int		f_map;
	int		f_minimap;
}				t_player;

typedef struct s_images
{
	void *mm_space[40];
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

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}	t_texture;

typedef struct s_info
{
	t_data		**mapa;
	int			fd;
	int			width;
	int			height;
	t_player	player;
	t_rgb		*sky;
	t_rgb		*floor;
	t_texture	*texture;
}	t_info;

int		draw(t_info *map);
t_info	*parser(int argc, char **argv, int fd);

#endif