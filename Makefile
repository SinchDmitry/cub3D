# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2022/04/03 18:35:18 by utygett          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=		cub3D

SRC			=		cub.c 						\
					parser/parser_main.c		\
					parser/parser_par.c			\
					parser/parser_map.c			\
					parser/parser_utils.c		\
					parser/parser_obj.c			\
					draw/draw.c					\
					draw/draw_init.c			\
					draw/draw_minimap_1.c		\
					draw/draw_minimap_2.c		\
					draw/draw_scene.c			\
					draw/draw_map.c				\
					draw/draw_key.c				\
					draw/draw_sprite.c			\
					draw/draw_sprite_check.c	\
					draw/draw_mouse.c			\
					draw/draw_mlx.c				\
					draw/draw_slide.c			\
					draw/draw_door.c			\
					draw/draw_door_init.c		\
					draw/draw_ray.c				\
					draw/draw_ray_init.c		\
					draw/draw_utils.c			\
					draw/draw_move_sprite.c 	\

FTDIR		= 		./libft/

LIBFT		= 		libft.a

MLX_PATH	=		mlx/

MLX			=		$(MLX_PATH)libmlx.a
		
OBJ_M		=		$(SRC:%.c=%.o)

DEP			=		$(SRC:%.c=%.d)

CFLAGS		=		-MD -Imlx -g -Werror -Wall -Wextra 
# -fsanitize=address 


CC		=	gcc -O2

RM		=	rm -f

all		:	libmake $(NAME)

$(NAME)	:	$(OBJ_M) $(FTDIR)$(LIBFT)
			$(CC) $(CFLAGS) $(OBJ_M) $(FTDIR)$(LIBFT) -L$(MLX_PATH) -lmlx -framework \
				OpenGL -framework AppKit -o $(NAME)
bonus	:	all

libmake	:	
			@make -C $(FTDIR)
			@make -C $(MLX_PATH)	
 
%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@make clean -C $(FTDIR)
			@make clean -C $(MLX_PATH) 
			$(RM) $(OBJ_M) $(DEP)

fclean	:	clean
			@make fclean -C $(FTDIR)
			$(RM) $(NAME)
	
re		:	fclean all

-include $(DEP)

.PHONY	:	all clean fclean re bonus