# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apintus <apintus@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 12:43:39 by apintus           #+#    #+#              #
#    Updated: 2024/10/08 16:51:25 by apintus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################################
## ARGUMENTS

NAME = cub3D
HEADER = includes/cub3d.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g3
MLX = -L mlx -l mlx -I mlx -lXext -lX11 -lm -lz


# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

##########################################################
## SOURCES

SRCS = srcs/main.c\
		srcs/exit.c\
		srcs/parsing/checker_file.c\
		srcs/parsing/get_file.c\
		srcs/parsing/get_info.c\
		srcs/parsing/get_texture.c\
		srcs/parsing/get_color.c\
		srcs/parsing/check_info.c\
		srcs/parsing/check_map.c\
		srcs/parsing/check_map2.c\
		srcs/parsing/check_map_utils.c\
		srcs/parsing/init_map.c\
		srcs/parsing/init_game.c\
		srcs/raycasting/raycasting.c\
		srcs/raycasting/raycasting2.c\
		srcs/raycasting/visual_2d.c\
		srcs/raycasting/vector_utils.c\
		srcs/raycasting/movement.c\
		srcs/raycasting/movement_utils.c\
		srcs/raycasting/colors_utils.c\
		srcs/raycasting/texture.c\
		srcs/raycasting/dda.c\
		srcs/raycasting/dda_utils.c\
		srcs/key_handler.c\

OBJS = $(SRCS:.c=.o)

# LIBFT
LIBFT_DIR = libft
LIBFT_MAKE_COMMAND = make -s -C $(LIBFT_DIR)
LIBFT_PATH = $(LIBFT_DIR)/libft.a

##########################################################
## RULES

all : $(NAME) $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT_PATH)
	make -C mlx
	@echo "$(GREEN)Linking libraries and building $@...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_PATH) $(MLX) -o $(NAME)
	@echo "$(GREEN)Success \n$(RESET)"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PATH) :
	@$(LIBFT_MAKE_COMMAND)

clean :
	@echo "$(RED)Cleaning object files...🧹$(RESET)"
	@$(RM) $(OBJS) $(ARCHIVE)
	@$(LIBFT_MAKE_COMMAND) clean
	make -C mlx clean

fclean : clean
	@echo "$(RED)Cleaning all files...🧹$(RESET)"
	@$(RM) $(NAME)
	@$(LIBFT_MAKE_COMMAND) fclean

re : fclean all

.PHONY : all clean fclean re
