# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/11/19 14:20:26 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -I$(MLX_DIR) -g

RM			=	/bin/rm -f

LIBFT_DIR	=	libft
LIBFT       =	$(LIBFT_DIR)/libft.a

# MLX_DIR		=	minilibx_macos
# MLX			=	$(MLX_DIR)/libmlx.dylib

MLX_DIR		=	minilibx-linux
MLX_SSH		=	git@github.com:42paris/minilibx-linux.git
MLX			=	$(MLX_DIR)/libmlx.a
MLX_FLAGS	=	-L./$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS        = 	$(shell find src -type f -name "*.c")

MAIN_SRC    = 	src/main.c

OBJ_DIR     =	obj
OBJS        =	$(SRCS:%.c=$(OBJ_DIR)/%.o)
ALL_OBJS    =	$(OBJS)

#******************************************************************************#
#									   RULES								   #
#******************************************************************************#

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) 1>/dev/null

$(MLX):
	@$(MAKE) -C $(MLX_DIR) 1>/dev/null

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ $(NAME) built"

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean 1>/dev/null
	@if [ -d "$(MLX_DIR)" ]; then $(MAKE) -C $(MLX_DIR) clean 1>/dev/null; fi
	@$(RM) -rf $(OBJ_DIR)
	@echo "✅  Objects files deleted"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean 1>/dev/null
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅  Binaries deleted"

re: fclean all

val: all
	valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all -s ./$(NAME)

minilibx:
	@if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_SSH); \
		echo "✅ Minilibx cloned"; \
	else \
		echo "Minilibx yet present"; \
	fi
	$(MAKE) -C $(MLX_DIR)

dev:
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Libraries created and objects deleted"

.PHONY: all clean fclean re dev val
