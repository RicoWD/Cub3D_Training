# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erpascua <erpascua@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 02:58:34 by erpascua          #+#    #+#              #
#    Updated: 2025/11/17 15:08:48 by erpascua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#******************************************************************************#
#									  CONFIG								   #
#******************************************************************************#

NAME		= 	cub3D
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -Iinclude -I$(LIBFT_DIR) -Iminilibx-linux -MMD -MP -g
LDFLAGS		=	-Lminilibx-linux -lmlx -lXext -lX11 -lm

RM			=	/bin/rm -f

LIBFT_DIR	=	libft
LIBFT       =	$(LIBFT_DIR)/libft.a

MLX_DIR		=	minilibx-linux
MLX			=	$(MLX_DIR)/libmlx.a

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
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)
	@echo "✅ $(NAME) built"

$(OBJ_DIR)/src/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean 1>/dev/null
	@$(MAKE) -C $(MLX_DIR) clean 1>/dev/null
	@$(RM) -rf $(OBJ_DIR)
	@echo "✅  Objects files deleted"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean 1>/dev/null
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "✅  Binaries deleted"

re: fclean all

val: all
	valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all -s ./$(NAME)

dev:
	@make re 1>/dev/null
	@make clean 1>/dev/null
	@echo "✅  Libraries created and objects deleted"

.PHONY: all clean fclean re dev val
