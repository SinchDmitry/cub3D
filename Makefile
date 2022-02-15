# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2022/02/15 16:21:31 by aarchiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

SRC		=	cub.c	parser/p_main.c parser/p_par.c	parser/p_map.c

FTDIR	= 	./libft/

LIBFT	= 	libft.a

# MLXDIR

# LIBMLX
			
OBJ_M	=	$(SRC:%.c=%.o)

DEP		=	$(SRC:%.c=%.d)

CFLAGS	=	-MD -Imlx 
# -fsanitize=address
#			-Werror -Wall -Wextra

CC		=	gcc

RM		=	rm -f

all		:	libmake $(NAME)

$(NAME)	:	$(OBJ_M)
			@cp $(FTDIR)$(LIBFT) .
			$(CC) $(CFLAGS) $(OBJ_M) libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)

libmake	:	
			@make -C $(FTDIR)

%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			@make clean -C $(FTDIR)
			$(RM) $(OBJ_M) $(DEP)

fclean	:	clean
			$(RM) $(NAME) $(LIBFT)
	
re		:	fclean all

-include $(DEP)

.PHONY	:	all clean fclean re 