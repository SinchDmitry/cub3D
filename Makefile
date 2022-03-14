# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2022/03/13 15:49:34 by aarchiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

SRC		=	cub.c	parser/p_main.c \
					parser/p_par.c	\
					parser/p_map.c \
					draw/draw.c \
					draw/draw_minimap.c\
					draw/draw_scene.c \
					draw/draw_map.c \
					draw/draw_ray.c \
					draw/draw_key.c \
					draw/draw_mouse.c

FTDIR	= 	./libft/

LIBFT	= 	libft.a

MLX_PATH	=		mlx/

MLX			=		$(MLX_PATH)libmlx.a
# MLXDIR

# LIBMLX
		
OBJ_M	=	$(SRC:%.c=%.o)

DEP		=	$(SRC:%.c=%.d)

CFLAGS	=	-MD -Imlx -g
# -fsanitize=address
#			-Werror -Wall -Wextra

CC		=	gcc

RM		=	rm -f

all		:	libmake $(NAME)

$(NAME)	:	$(OBJ_M)
			@cp $(FTDIR)$(LIBFT) .
			$(CC) $(CFLAGS) $(OBJ_M) libft.a -L$(MLX_PATH) -lmlx -framework \
				OpenGL -framework AppKit -o $(NAME)

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
			$(RM) $(NAME) $(LIBFT) $(MLX)
	
re		:	fclean all

-include $(DEP)

.PHONY	:	all clean fclean re 