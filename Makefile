# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cpieri <cpieri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/15 11:20:25 by cpieri            #+#    #+#              #
#    Updated: 2018/06/28 11:24:52 by cvautrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	rt

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -O3 -flto #-g -fsanitize=address -fno-omit-frame-pointer

FW_PATH = frameworks

SDL_PATH = $(FW_PATH)/SDL2.framework

IMG_PATH = $(FW_PATH)/SDL2_image.framework

TTF_PATH = $(FW_PATH)/SDL2_ttf.framework

SDL_FLAGS = -F $(FW_PATH) -framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath $(FW_PATH)

SDL_LOCAL_FLAGS = -framework SDL2 -F $(FW_PATH) -framework SDL2_image -framework SDL2_ttf -rpath $(FW_PATH)

CPPFLAGS=	-Iincludes

FLAGSFT	=	-L./libft -lft -L./libgraph -lgraph

SRC_PATH=	srcs

OBJ_PATH=	obj

SRC_NAME= 	main.c				\
			display.c			\
			init_struct.c		\
			inputs.c			\
			utils.c				\
			intersection.c		\
			normal.c			\
			camera.c			\
			img.c				\
			rotation_matrix.c	\
			ray_adapter.c		\
			light.c				\
			exit.c				\
			filter.c 			\
			ui.c				\
			textures.c			\
			limit.c				\
			sdl_init.c			\
			parser.c			\
			parser_check_print.c\
			parser_get_objs.c	\
			parser_get_lights.c	\
			parser_sc_infos.c	\
			parser_utils.c		\
			draw_ui.c			\
			setf_btn.c			\
			button_event.c		\
			textures_setup.c	\
			screenshot.c		\
			new_objs.c			\
			perlin.c			\
			perlin_init.c		\
			free_ui.c			\
			filter_2.c			\
			fastmode_complete.c	\
			transparency.c		\
			parser_grab_objs.c	\
			parser_grab_extras.c\
			change_sc.c			\
			ui_filters.c		\
			command.c			\
			ui_command.c		\
			get_intersection.c	\
			cam_move.c			\
			get_shape.c			\
			command_rot.c		\
			blur_mode.c			\
			check_light.c


OBJ_NAME=	$(SRC_NAME:.c=.o)

SRC		=	$(addprefix $(SRC_PATH)/,$(SRC_NAME))

OBJ		=	$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

NONE = \033[0m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m

.PHONY:	all clean fclean re echo norm

all:		LFT LGRAPH $(NAME)

$(NAME):	libft echo $(OBJ)
			@if [ -d "/Library/Frameworks/SDL2.framework" ]; then \
			$(CC) $(CFLAGS) $(FLAGSFT) -o $(NAME) $(OBJ) $(CPPFLAGS) $(SDL_LOCAL_FLAGS); \
			else \
			$(CC) $(CFLAGS) $(FLAGSFT) -o $(NAME) $(OBJ) $(CPPFLAGS) $(SDL_FLAGS); \
			fi
			@echo "\n$(GREEN)$(NAME) compiled !$(NONE)"

echo:
			@ echo -n Compiling files

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c includes/rt.h libft/libft.a libgraph/libgraph.a
			@mkdir $(OBJ_PATH) 2> /dev/null || true
			@if [ -d "/Library/Frameworks/SDL2.framework" ]; then \
			$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -I/Library/Frameworks/SDL2.framework/Headers/ -I $(IMG_PATH)/Headers -I $(TTF_PATH)/Headers -o $@; \
			else \
			$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -I $(SDL_PATH)/Headers -I $(TTF_PATH)/Headers -I $(IMG_PATH)/Headers -o $@; \
			fi
			@echo -n .

clean:
			@echo "$(YELLOW)Cleaning...$(NONE)"
			@make clean -C ./libft/
			@make clean -C ./libgraph/
			@/bin/rm -f $(OBJ)
			@rmdir $(OBJ_PATH) 2> /dev/null || true
			@/bin/rm -rf $(PATH_SDL)

fclean:		clean
			@make fclean -C ./libft/
			@echo "$(RED)Libft.a deleted$(NONE)"
			@make fclean -C ./libgraph/
			@echo "$(RED)Libgraph.a deleted$(NONE)"
			@/bin/rm -f $(NAME)
			@echo "$(RED)$(NAME) deleted !$(NONE)"

norm:		clean
			@echo "$(CYAN)Running norminette...$(NONE)"
			@norminette $(SRC_PATH) $(INCLUDE) libft/ libgraph/ \
				| grep -B 1 '^Error' 2> /dev/null || echo '$(GREEN)Norme OK !$(NONE)';

re:			fclean all

LFT:
		@if [ ! "./libft/libft.a" ]; then \
			make -C ./libft/; \
			echo "\n$(GREEN)Libft compiled !$(NONE)";\
		else \
			echo "$(GREEN)Libft was already installed$(NONE)"; \
		fi

LGRAPH:
		@if [ ! "./libgraph/libgraph.a" ]; then \
			make -C ./libgraph/; \
			echo "\n$(GREEN)Libgraph compiled !$(NONE)";\
		else \
			echo "$(GREEN)Libgraph was already installed$(NONE)"; \
		fi
