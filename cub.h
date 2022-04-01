/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 14:57:59 by aarchiba          #+#    #+#             */
/*   Updated: 2022/04/01 18:44:08 by aarchiba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "math.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# define P_BACK 			2
# define P_FRONT 			1
# define HEIGHT				700
# define WIDTH 				1000
# define MAX_KEYS_NUM		260
# define SPR_NUM			4
# define DOOR_NUM			4
# define COMP_COSTUME		22
# define SPR_COSTUME		11
# define SPACE_TEXTURE		40
# define WALL_TEXTURE		4
# define BONUS_MODE			1
# define FULL_SIZE			1
# define AMONG_SIZE			0

typedef struct s_par_f
{
	short int	sky;
	short int	west;
	short int	east;
	short int	south;
	short int	north;
	short int	floor;
}	t_par_f;

typedef struct s_play
{
	float		x;
	float		y;
	float		a;
	float		dir;
	float		dir_x;
	float		dir_y;
	short int	f_map;
	float		x_textu;
	float		y_textu;
	short int	f_minimap;
	short int	side_for_move;
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
	int		vertilcal_pos;
}	t_cam;

typedef struct s_images
{
	void	*mm_space[40];
	void	*compas;
}	t_images;

typedef struct s_par_slot
{
	int		door;
	char	sym;
}	t_par_slot;

typedef struct s_par_tex
{
	char	*east;
	char	*west;
	char	*north;
	char	*south;
}	t_par_tex;

typedef struct s_map_info
{
	int			fd;
	int			width;
	int			height;
	int			sky_color;
	int			floor_color;
	t_cam		cam;
	t_play		play;
	t_par_f		flags;
	t_par_slot	**mapa;
	t_par_tex	*texture;
}	t_map_info;

typedef struct s_door_struct
{
	short int	use;
	short int	start;
	short int	end;
	short int	text_x;
	short int	text_y;
	short int	step;
	double		tex_pos;
}	t_door_st;

typedef struct s_cost_tex
{
	void		*img;
	char		*addr;
	int			img_h;
	int			img_w;
	int			endian;
	int			line_length;
	int			bits_per_pixel;
}	t_cost_tex;

typedef struct s_wall_tex
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	char			sym;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	unsigned int	col;
	// t_tex			wall[4];
}	t_wall_tex;

/*	t_spr_tex	spr_img[SPR_NUM];
	t_spr_tex	door_img[DOOR_NUM];
	t_spr_tex	comp_img;	*/
typedef struct s_data_tex
{
	int			num;
	float		inv;
	float		dist;
	int			len_am;
	int			len_comp;
	t_cost_tex	am_costumes[SPR_COSTUME];
	t_cost_tex	comp_costumes[COMP_COSTUME];
	t_cost_tex	wall_textures[WALL_TEXTURE];
	t_cost_tex	space_textures[SPACE_TEXTURE];
	t_spr_tex	*spr_img;
	t_spr_tex	*comp_img;
	//t_xxx_xxx	*wall_img;
	//t_xxx_xxx	*space_img;
}	t_data_tex;

/* t_tex		costumes[COMP_COSTUME] */	
typedef struct s_spr_tex
{
	float				x;
	float				y;
	int					d;
	float				t_y;
	float				t_x;
	int					shot;
	int					dead;
	int					tex_x;
	int					tex_y;
	float				x_ray;
	float				y_ray;
	int					h_spr;
	int					w_spr;
	int					dr_f_x;
	int					dr_f_y;
	int					dr_st_x;
	int					dr_st_y;
	int					fact_f_x;
	int					fact_st_x;
	int					pos_spr_x;
	int					num_of_spr;
	int					size;
	static	int			c_i;
	struct s_spr_tex	*next;
}	t_spr_tex;

typedef struct s_data_mlx
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			map_zoom;
	float		ray_a;
	float		sector[WIDTH];
	int			keycode[MAX_KEYS_NUM];
	int			mouse_code[10]; // ?
	int			aim_size;
	int			mouse_x;
	int			mouse_y;
	int			prev_mouse_x;
	int			prev_mouse_y;
	t_door_st	*door_struct;
	t_cost_tex	weapon;
	t_images	image;
	t_map_info	*map;
	t_data_tex	*am_s;
	t_wall_tex	*wall_img;
}	t_data_mlx;

int			draw(t_data_mlx	*data);
t_map_info	*parser(t_data_mlx *data, int argc, char **argv, int fd);

#endif
