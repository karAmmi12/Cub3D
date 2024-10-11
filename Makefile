# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kammi <kammi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/15 12:43:39 by apintus           #+#    #+#              #
#    Updated: 2024/10/11 18:19:15 by kammi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------------------------------------------------- #
#                                   NAME                                       #

NAME = cub3D

#----------------------------------------------------------------------------- #
#                                   COMPILATION                                #

CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -MMD -g3 -O3 -ffast-math -I./include

# ---------------------------------------------------------------------------- #
#                                   LIBRARIES                                  #


LIBFTDIR = ./libft
MLXDIR = ./mlx
MLXFLAG = -L$(MLXDIR) -lmlx -L/usr/lib -lXext -lX11 -lm

# ---------------------------------------------------------------------------- #
#                                   COLORS                                     #

GREEN   := \033[38;5;76m
RED     := \033[38;5;160m
YELLOW  := \033[38;5;226m
RESET   := \033[00m


# ---------------------------------------------------------------------------- #
#                                   SOURCES                                    #

SRC = $(addsuffix .c, \
		main \
		init \
		key_handler)

SRC += $(addprefix parsing/, $(addsuffix .c, \
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

SRC += $(addprefix game/, $(addsuffix .c, \
		raycasting \
		raycasting2 \
		vector_utils \
		movement \
		movement_utils \
		colors_utils \
		texture \
		dda \
		dda_utils))

SRC += $(addprefix cleaning/, $(addsuffix .c, \
		exit \
		exit_utils))


SRCS_DIR := ./srcs
OBJS_DIR := ./objs

SRCS := $(addprefix $(SRCS_DIR)/, $(SRC))
OBJS := $(addprefix $(OBJS_DIR)/, $(SRC:.c=.o))
DEPS := $(OBJS:.o=.d)

HEADERS := ./includes


O_SUBDIR := $(sort $(dir $(OBJS)))

# ---------------------------------------------------------------------------- #
#                                   RULES                                      #

all : $(NAME)

$(NAME): $(OBJS)
	@make --silent -C ${LIBFTDIR}
	@echo "$(YELLOW)[Compilation]$(RESET) Compilation de la bibliothèque MLX..."
	@make --silent -C ${MLXDIR}  > /dev/null 2>&1
	@$(CC) -I$(HEADERS) -I$(MLXDIR) -o $@ $(OBJS) -L$(LIBFTDIR) -lft $(MLXFLAG) $(LDFLAG) $(CFLAGS)
	@echo "$(GREEN)[Succes]$(RESET) Compilation de $@ terminée."
	@printf "$(RED)"
	@echo "   ___ _                                       _                     "
	@echo "  / __(_)_ __ ___ _   _ ___   /\\/\\   __ ___  _(_)_ __ ___  _   _ ___ "
	@echo " / /  | | '__/ __| | | / __| /    \\ / _\` \\ \\/ / | '_ \` _ \\| | | / __|"
	@echo "/ /___| | | | (__| |_| \\__ \\/ /\\/\\ \\ (_| |>  <| | | | | | | |_| \\__ \\"
	@echo "\\____/|_|_|  \\___|\\__,_|___/\\/    \\/\\__,_/_/\\_\\_|_| |_| |_|\\__,_|___/"
	@echo "                                                                    "
	@printf "$(RESET)"


$(OBJS_DIR) $(O_SUBDIR):
	@mkdir -p $@

-include $(DEPS)


$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(O_SUBDIR)
	@$(eval TOTAL := $(words $(OBJS)))
	@$(eval COUNT := $(shell expr $(COUNT) + 1))
	@echo -n "$(YELLOW)[Compilation]$(RESET) Compilation de $<" $(COUNT)"/"$(TOTAL)"\r"
	@$(CC) $(CFLAGS) -I$(HEADERS) -I$MLXDIR -c $< -o $@ >> /dev/null 2>&1
	@echo -n "$(YELLOW)[Compilation]$(RESET) Compilation de $<" $(COUNT)"/"$(TOTAL)"\r"


clean:
	@echo -n "$(RED)Cleaning object files... 🧹$(RESET)"
	@make --silent clean -C ${LIBFTDIR} /dev/null 2>&1
	@make --silent clean -C ${MLXDIR} /dev/null 2>&1
	@rm -rf $(OBJS_DIR)
	@for i in {1..10}; do echo -n "."; sleep 0.1; done; echo ""

fclean: clean
	@echo -n "$(RED)Cleaning all files... 🗑️$(RESET)"
	@make --silent fclean -C ${LIBFTDIR} /dev/null 2>&1
	@make --silent clean -C ${MLXDIR} /dev/null 2>&1
	@rm -f $(NAME)
	@for i in {1..10}; do echo -n "."; sleep 0.1; done; echo ""

re: fclean all

.PHONY: all clean fclean re val run
