# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aarchiba < aarchiba@student.21-school.r    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2022/02/13 18:52:32 by aarchiba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

SRC		=	parser/p_main.c 

FTDIR	= 	./libft/

LIBFT	= 	libft.a

# MLXDIR

# LIBMLX
			
OBJ_M	=	$(SRC:%.c=%.o)

DEP		=	$(SRC:%.c=%.d)

CFLAGS	=	-MD -Imlx
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
			$(RM) $(OBJ_M) $(DEP)

fclean	:	clean
			$(RM) $(NAME)
	
re		:	fclean all

-include $(DEP)

.PHONY	:	all clean fclean re 