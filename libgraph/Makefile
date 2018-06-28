# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/01 15:43:04 by cpieri            #+#    #+#              #
#    Updated: 2018/06/28 12:46:38 by cvautrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libgraph.a

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SRC_PATH=	srcs

OBJ_PATH=	obj

CPPFLAG	=	-Iinclude

DEPS =		Makefile			\
			include/bloc.h		\
			include/color.h		\
			include/libgraph.h	\
			include/vector.h	\
			include/button.h	\
			include/label.h		\
			include/matrix.h

SRCS = 		matrix.c			\
			rotation_matrix.c	\
			vector_new.c		\
			vector.c			\
			vector_product.c	\
			colors.c			\
			button.c			\
			bloc.c				\
			bloc_2.c			\
			label.c				\
			vector_2d_op.c		\
			objs.c


OBJS	=	$(SRCS:.c=.o)

SRC		=	$(addprefix $(SRC_PATH)/,$(SRCS) )

OBJ		=	$(addprefix $(OBJ_PATH)/,$(OBJS) )

.PHONY: all clean fclean re echo

all:		echo $(NAME)

$(NAME): 	$(OBJ)
			@ar rc $(NAME) $(OBJ) ../libft/libft.a
			@ranlib $(NAME)

echo:
			@echo -n Getting libgraph ready

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(DEPS)
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			@$(CC) $(CFLAGS) $(CPPFLAG) -o $@ -c $<
			@echo -n .

clean:
			@/bin/rm -f $(OBJ)
			@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean:		clean
			@/bin/rm -f $(NAME)

re:			fclean all
