# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: inowak-- <inowak--@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/13 12:50:03 by inowak--          #+#    #+#              #
#    Updated: 2025/03/20 05:44:24 by inowak--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

########################
#        Color         #
########################

RED    = \033[1;31m
GREEN  = \033[1;32m
YELLOW = \033[1;33m
BLUE   = \033[1;34m
CYAN   = \033[1;36m
PURPLE = \033[1;35m
SPRUCE_GREEN = \033[38;2;0;102;51m
KING_BLUE = \033[38;2;65;105;225m
RESET  = \033[0m

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
NAME = cub3d

SRC = src/main.c \
	  src/parsing/parsing.c \
	  src/parsing/create_map.c \
	  src/parsing/identifier.c \
	  src/parsing/flood_fill.c \
	  src/display/window.c

GNL_SRC = lib/GNL/get_next_line.c \
	  lib/GNL/get_next_line_utils.c

OBJ_DIR = .objects
INCLUDE_DIR = includes
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
GNL_OBJ = $(GNL_SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = lib/libft
OBJ_LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = lib/minilibx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

########################
#        Rules         #
########################

all: $(NAME)

$(OBJ_LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus > /dev/null
	@printf "$(GREEN)libft compiled successfully!$(RESET)\n"

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR) > /dev/null
	@printf "$(GREEN)MiniLibX compiled successfully!$(RESET)\n"

$(NAME): $(OBJ) $(GNL_OBJ) $(OBJ_LIBFT) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJ) $(GNL_OBJ) $(OBJ_LIBFT) $(MLX_FLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -o $(NAME)
	@printf "$(PURPLE) _____       _      _____     _ \n"
	@printf "$(PURPLE)/  __ \     | |    |____ |   | |\n"
	@printf "$(PURPLE)| /  \/_   _| |__      / / __| |\n"
	@printf "$(PURPLE)| |   | | | |  _ \     \ \/ _  |\n"
	@printf "$(PURPLE)| \__/\ |_| | |_| | ___/ / |_| |\n"
	@printf "$(PURPLE) \____/\__ _|_ __/ \____/ \__ _|\n"
	@printf "$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR)/includes -I$(MLX_DIR) -O0 -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null
	@$(MAKE) -C $(MLX_DIR) clean > /dev/null
	@printf "$(GREEN)clean$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)fclean$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re