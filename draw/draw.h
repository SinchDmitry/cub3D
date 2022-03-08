/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/03/08 20:03:40 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include "../cub.h"
// #define WIDTH 1280
// #define HEIGHT 720
# define WIDTH 				1000
# define HEIGHT				700
# define WHITE_COL			0x00FFFFFF
# define RED_COL			0x00FF0000
# define BLUE_COL			0x000000FF
# define GREEN_COL 			0x0000FF00
# define MINIMAPWIDTH		200
# define MINIMAPHEIGHT		200
# define STATUS_BAR_HEIGHT	100
# define INVISIBLE_COL		0xFF000000
# define PLAYERCOL			0x00FFFFFF
# define WALLCOL			0x00708090
# define FLOORCOL			0x00aab8c4
# define RAYCOL				0x0000000F
# define MM_BOARD_COL		0x00FFFFF0
# define MM_BOARD_SIZE		5
# define TEXSIZE		15 // need auto size map after parse file
# define MMTEXSIZE		20
# define MOVE_SPEED			0.2
# define MOVE_ANGLE			0.05
# define VIEW_RANGE			35.0f
# define W_KEY				13
# define A_KEY				0
# define S_KEY				1
# define D_KEY				2
# define LEFT_KEY			123
# define RIGHT_KEY			124
# define DOWN_KEY			125
# define MAP_KEY			48
# define UP_KEY				126
# define MINIMAP_KEY		46
# define ADD_PAD_KEY		69
# define SUB_PAD_KEY		78
# define MOVEX				100
# define MOVEY				100
# define ROTATE_MOV			3.1415f
# define INVERSE			2.35f
# define FOV				1.571f
// # define ANG_START			-0.75f
// # define ANG_STEP			0.0015f
# define MMFOV				0.55f
# define MMANG_START		-0.55f
# define MMANG_STEP			0.02f

struct					s_images;
typedef struct s_images	t_images;

typedef struct s_data_mlx {
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img1;
	char		*addr1;
	int			bits_per_pixel1;
	int			line_length1;
	int			endian1;
	int			map_zoom;
	float		ray_a;
	float		sector;
	t_images	image;
	t_info		*map;
}				t_data_mlx;

typedef struct s_line
{
	float	delta_x;
	float	delta_y;
	float	tmp_delta;
	float	sign_x;
	float	sign_y;
	float	error;
	float	error2;
	int		flag;
	float	st_x1;
	float	st_x2;
	float	st_y1;
	float	st_y2;
}	t_line;

typedef struct s_vls
{
	float	x1;
	float	x2;
	float	y1;
	float	y2;
}	t_vls;

void			draw_map_with_move(t_data_mlx *data);
void			my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color);
unsigned int	my_mlx_get_pixel(t_data_mlx *data, int x, int y, int wall);
void			draw_fvp(t_data_mlx *data);
int				key_h(int keycode, t_data_mlx *data);
void			draw_map(t_data_mlx *data);
int				check_move(t_data_mlx *data);
int				render_next_frame(t_data_mlx *data);
void			ray_player(t_data_mlx *data, int flag);
void			draw_invis_background(t_data_mlx *data, int height, int width);
void			draw_ray_cast(t_data_mlx *data, float x, float h, int w_pix);
int				step_counter_texture(float step, float value);

#endif
