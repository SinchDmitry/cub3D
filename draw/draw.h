/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/02/20 21:26:39 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef DRAW_H
# define DRAW_H
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../cub.h"
// #define WIDTH 1280
// #define HEIGHT 720
# define WIDTH 2000
# define HEIGHT 1000
# define WHITE_COL 0x00FFFFFF
# define MINIMAPWIDTH 300
# define MINIMAPHEIGHT 300
# define STATUS_BAR_HEIGHT 100
# define INVISIBLE_COL 0xFF000000
# define PLAYERCOL 0x00FFFFFF
# define WALLCOL 0x0000FFFF
# define FLOORCOL 0x000000FF
# define RAYCOL 0x0000000F
# define MM_BOARD_COL 0x00FFFFF0
# define MM_BOARD_SIZE 5
# define TEXTURESIZE 36 // need auto size map after parse file
# define MMTEXTURESIZE 20
# define MOVE_SPEED 0.2
# define MOVE_ANGLE 0.2
# define VIEW_RANGE 40
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define DOWN_KEY 125
# define MAP_KEY 48
# define UP_KEY 126
# define MOVEX 150
# define MOVEY 150
# define ROTATE_MOV 3.1415f
# define INVERSE 2.35f
# define FOV 0.75f
# define ANG_START -0.75f
# define ANG_STEP 0.004f
typedef struct	s_data_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		sector[(int)((FOV - ANG_START) / ANG_STEP) + 1];
	t_images	image;
	t_info  *map;
}				t_data_mlx;

void	draw_map_with_move(t_data_mlx *data);
void	my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color);
// void draw_fvp(t_data_mlx *data);


#endif

