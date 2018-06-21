# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 15:43:04 by cpieri            #+#    #+#              #
#    Updated: 2018/06/21 14:14:20 by cvautrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libgraph.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INCS	=	libgraph.h

HEADERS	=	./libgraph.h

SRC_PATH=	srcs

OBJ_PATH=	obj

CPPFLAG	=	-Iinclude

SRCS = 		matrix.c			\
			rotation_matrix.c	\
			vector_new.c		\
			vector.c			\
			vector_product.c	\
			colors.c			\
			button.c			\
			bloc.c				\
			label.c				\
			vector_2d_op.c		\
			objs.c


OBJS	=	$(SRCS:.c=.o)

SRC		=	$(addprefix $(SRC_PATH)/,$(SRCS) )

OBJ		=	$(addprefix $(OBJ_PATH)/,$(OBJS) )

.PHONY: all clean fclean re

all:		$(NAME)

$(NAME): 	$(OBJ)
			@echo "compiling libgraph.a"
			@ar rc $(NAME) $(OBJ) ../libft/libft.a
			@ranlib $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			$(CC) $(CFLAGS) $(CPPFLAG) -o $@ -c $<

clean:
			@/bin/rm -f $(OBJ)
			@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:		clean
			@echo "cleaning libgraph.a"
			@/bin/rm -f $(NAME)

re:			fclean all
