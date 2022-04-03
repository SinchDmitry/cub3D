/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:55:55 by utygett           #+#    #+#             */
/*   Updated: 2022/04/03 17:13:40 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../cub.h"

/* colors */
# define WHITE_COL			0x00FFFFFF
# define RED_COL			0x00FF0000
# define BLUE_COL			0x0000BFFF
# define GREEN_COL 			0x0000FF00
# define INVISIBLE_COL		0xFF000000
# define PLAYERCOL			0x00FFFFFF
# define WALLCOL			0x00708090
# define FLOORCOL			0x00AAB8C4

/* minimap */
# define MINIMAPWIDTH		200
# define MINIMAPHEIGHT		200
# define MM_BOARD_SIZE		5
# define MMTEXSIZE			20
# define MOVEX				100
# define MOVEY				100
# define ROTATE_MOV			3.1415f
# define FOV				1.571f
# define MMFOV				0.80f
# define MMANG_START		-0.80f
# define MMANG_STEP			0.05f

/* move */
# define MOVE_SPEED			0.05
# define MOVE_ANGLE			0.05
# define VIEW_RANGE			35.0f

/* keys */
# define W_KEY				13
# define A_KEY				0
# define S_KEY				1
# define D_KEY				2
# define E_KEY				14
# define Q_KEY				12
# define LEFT_KEY			123
# define RIGHT_KEY			124
# define DOWN_KEY			125
# define MAP_KEY			48
# define UP_KEY				126
# define SHIFT_KEY			257
# define MINIMAP_KEY		46
# define ADD_PAD_KEY		69
# define SUB_PAD_KEY		78
# define MOUSE_LEFT_KEY		1
# define PRESS				1
# define UNPRESS			0

/* weapon */
# define AIM_SIZE			40
# define AIM_WIDTH			1
# define LASER_WIDTH		3

/* sprites */
# define MOVE_STEP_SPRITE 	0.05f
# define WALL_COLLISION 	0.2f

typedef struct s_images			t_images;
typedef struct s_spr_tex		t_spr_tex;
typedef struct s_data_mlx		t_data_mlx;
typedef struct s_door_str		t_door_str;
typedef struct s_cost_tex		t_cost_tex;
typedef struct s_data_tex		t_data_tex;
typedef struct s_wall_tex		t_wall_tex;

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

typedef struct s_ref
{
	char	*among_dir;
	char	*comp_dir;
	char	*wall_dir;
	char	*space_dir;
	char	*weapon_dir;
	char	*compas_dir;
	char	*door_dir;
}	t_ref;

/* map & minimap */
void			draw_map(t_data_mlx *data);
void			draw_board(t_data_mlx *data);
void			draw_minimap(t_data_mlx *data);
void			draw_map_with_move(t_data_mlx *data);
void			map_exit_case(int keycode, t_data_mlx *data);
void			pixel_put_map_move(int x, int y, t_data_mlx *data, int color);

/* player move & data */
void			ray_play(t_data_mlx *data);
void			wall_slide(t_data_mlx *data);
int				check_move(t_data_mlx *data);

/* draw door*/
void			check_door(t_data_mlx *data);
void			ray_wall_data(t_data_mlx *data, int x);
void			check_door_state(t_data_mlx *data, t_par_slot **mapa);
void			init_door_pix(t_data_mlx *data, int x, int door_state);

/* sprites */
void			init_sprites(t_data_mlx *data);
void			put_weapon_image(t_data_mlx *data);
void			check_sprite_position(t_data_mlx *data);
void			check_obj_in_map(t_data_mlx *data, t_spr_tex *tmp_img);
void			draw_sprite(t_data_mlx *data, t_spr_tex *img, t_cost_tex *cost);

/* textures */
void			draw_aim(t_data_mlx *data);
void			draw_map_with_move(t_data_mlx *data);

/* mouse & keyboard */
int				key_h(t_data_mlx *data);
void			mouse_move(t_data_mlx *data);
int				ft_mouse(int keycode, int x, int y, t_data_mlx *data);

/* ray calculation */
void			ray_init(t_data_mlx *data, int x);
void			ray_draw_lines(t_data_mlx *data, int x);

/* general draw */
void			draw_fvp(t_data_mlx *data);
void			draw_objects(t_data_mlx *data);
int				render_next_frame(t_data_mlx *data);
void			draw_line(t_data_mlx *data, t_vls xyz, int color);
unsigned int	my_mlx_get_pixel(t_cost_tex costume, int x, int y);
void			my_mlx_pixel_put(t_data_mlx *data, int x, int y, int color);
void			draw_invis_background(t_data_mlx *data, int height, int width);

#endif
