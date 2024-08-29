# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apintus <apintus@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 12:43:39 by apintus           #+#    #+#              #
#    Updated: 2024/08/29 16:57:57 by apintus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################################
## ARGUMENTS

NAME = cub3D
HEADER = includes/cub3d.h
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -g3

# Colors
RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

##########################################################
## SOURCES

SRCS = srcs/main.c\
		srcs/checker_file.c\
		srcs/exit.c\
		srcs/get_file.c\
		srcs/get_info.c\
		srcs/get_texture.c\
		srcs/get_color.c\
		srcs/check_info.c\
		srcs/check_map.c\
		srcs/check_map2.c\
		srcs/check_map_utils.c\

OBJS = $(SRCS:.c=.o)

# LIBFT
LIBFT_DIR = libft
LIBFT_MAKE_COMMAND = make -s -C $(LIBFT_DIR)
LIBFT_PATH = $(LIBFT_DIR)/libft.a

##########################################################
## RULES

all : $(NAME) $(LIBFT_PATH)

$(NAME) : $(OBJS) $(LIBFT_PATH)
	@echo "$(GREEN)Linking libraries and building $@...$(RESET)"
	@$(CC) $(OBJS) $(LIBFT_PATH) -o $(NAME)
	@echo "$(GREEN)Success \n$(RESET)"

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_PATH) :
	@$(LIBFT_MAKE_COMMAND)

clean :
	@echo "$(RED)Cleaning object files...🧹$(RESET)"
	@$(RM) $(OBJS) $(ARCHIVE)
	@$(LIBFT_MAKE_COMMAND) clean

fclean : clean
	@echo "$(RED)Cleaning all files...🧹$(RESET)"
	@$(RM) $(NAME)
	@$(LIBFT_MAKE_COMMAND) fclean

re : fclean all

.PHONY : all clean fclean re
