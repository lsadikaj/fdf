# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 11:39:04 by lsadikaj          #+#    #+#              #
#    Updated: 2025/02/11 18:46:12 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_DIR = srcs
INC_DIR = inc
LIBMLX_DIR = libmlx
LIBFT_DIR = libft

SRCS = $(SRC_DIR)/fdf.c $(SRC_DIR)/parse_map.c $(SRC_DIR)/parse_utils.c \
	$(SRC_DIR)/draw_map.c $(SRC_DIR)/draw_utils.c $(SRC_DIR)/event.c \
	$(SRC_DIR)/color.c $(SRC_DIR)/convert_utils.c \
	$(SRC_DIR)/projection.c $(SRC_DIR)/projection_utils.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR) -I$(LIBMLX_DIR) -I$(LIBFT_DIR)

MLX = -L$(LIBMLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = -L$(LIBFT_DIR) -lft

all: $(NAME)

$(NAME): $(OBJS) libmlx/libmlx.a libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(LIBFT)

libmlx/libmlx.a:
	make -C $(LIBMLX_DIR)

libft/libft.a:
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re