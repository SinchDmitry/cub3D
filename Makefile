# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 11:40:33 by utygett           #+#    #+#              #
#    Updated: 2022/02/10 15:35:40 by utygett          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

SRC		=	main.c 
			
OBJ_M	=	$(SRC:%.c=%.o)

DEP		=	$(SRC:%.c=%.d)

CFLAGS	=	-MD -Imlx

CC		=	gcc

RM		=	rm -f

all		:	$(NAME)

$(NAME)	:	$(OBJ_M)
			$(CC) $(CFLAGS) $(OBJ_M) -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	
%.o		:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

clean	:
			$(RM) $(OBJ_M) $(DEP)

fclean	:	clean
			$(RM) $(NAME)
	
re		:	fclean all

-include $(DEP)

.PHONY	:	all clean fclean re 