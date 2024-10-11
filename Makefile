# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kammi <kammi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 12:43:39 by apintus           #+#    #+#              #
#    Updated: 2024/10/11 12:40:31 by kammi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME = cub3D

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -MMD -g3 -O3 -ffast-math -I./include

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

LIBFTDIR = ./libft
MLXDIR = ./mlx
MLXFLAG = -L$(MLXDIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

FILES = $(addsuffix .c, \
		main \
		init \
		key_handler)

FILES += $(addprefix game/, $(addsuffix .c, \
		raycasting \
		raycasting2 \
		vector_utils \
		movement \
		movement_utils \
		colors_utils \
		texture \
		dda \
		dda_utils))

FILES += $(addprefix parsing/, $(addsuffix .c, \
		checker_file \
		get_file \
		get_info \
		get_texture \
		get_color \
		check_info \
		check_map \
		check_map2 \
		check_map_utils \
		init_map \
		init_game))

FILES += $(addprefix cleaning/, $(addsuffix .c, \
		exit \
		exit_utils))


SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := $(addprefix $(SRCS_DIR)/, $(FILES))
OBJS := $(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))
DEPS := $(OBJS:.o=.d)

HEADERS := ./includes


OBJ_SUBDIRS := $(sort $(dir $(OBJS)))

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all : $(NAME)

$(NAME): $(OBJS)
	@make --silent -C ${LIBFTDIR}
	@echo "$(LBLUE)[Compilation]$(RESET) Compilation de la bibliothèque MLX..."
	@make --silent -C ${MLXDIR}  > /dev/null 2>&1
	@$(CC) -I$(HEADERS) -I$(MLXDIR) -o $@ $(OBJS) -L$(LIBFTDIR) -lft $(MLXFLAG) $(LDFLAG) $(CFLAGS)
	@printf "$(RED)"
	@echo " ___ _                                       _                     "
	@echo "/ __(_)_ __ ___ _   _ ___   /\\/\\   __ ___  _(_)_ __ ___  _   _ ___ "
	@echo "/ /  | | '__/ __| | | / __| /    \\ / _\` \\ \\/ / | '_ \` _ \\| | | / __|"
	@echo "/ /___| | | | (__| |_| \\__ \\/ /\\/\\ \\ (_| |>  <| | | | | | | |_| \\__ \\"
	@echo "\\____/|_|_|  \\___|\\__,_|___/\\/    \\/\\__,_/_/\\_\\_|_| |_| |_|\\__,_|___/"
	@echo "                                                                    "
	@printf "$(RESET)"
# Create object directories
$(OBJS_DIR) $(OBJ_SUBDIRS):
	@mkdir -p $@

-include $(DEPS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_SUBDIRS)
	@printf "$(LBLUE)[Compilation]$(RESET) In progress... $(GREEN)$<" && \
	$(CC) $(CFLAGS) -I$(HEADERS) -I$(MLXDIR) -c $< -o $@ && \
	printf "\r$(LBLUE)[Compilation]$(RESET) Completed   ... $(GREEN)$<" && \
	printf "\n"

clean:
	@make clean -C ${LIBFTDIR}
	@make clean -C ${MLXDIR}
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C ${LIBFTDIR}
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re val run

# **************************************************************************** #
#                                   COLORS                                     #
# **************************************************************************** #

GREEN   := \033[38;5;76m
RED     := \033[38;5;160m
YELLOW  := \033[38;5;226m
ORANGE  := \033[38;5;202m
PURPLE  := \033[38;5;213m
LBLUE   := \033[38;5;51m
BLUE    := \033[38;5;117m
INDI    := \033[38;5;99m
RESET   := \033[00m
