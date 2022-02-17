/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:57:59 by aarchiba          #+#    #+#             */
/*   Updated: 2022/02/17 19:53:06 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "math.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "parser/parser.h"
# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_player {
	float	x;
	float	y;
	float	a;
	float	x_textu;
	float	y_textu;
	char	dir;
}				t_player;

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

#endif