# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsadikaj <lsadikaj@student.42lausanne.ch>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 11:39:04 by lsadikaj          #+#    #+#              #
#    Updated: 2025/12/04 11:31:29 by lsadikaj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRC_DIR = srcs
INC_DIR = inc
LIBFT_DIR = libft

SRCS = $(SRC_DIR)/fdf.c $(SRC_DIR)/parse_map.c $(SRC_DIR)/parse_utils.c \
	$(SRC_DIR)/draw_map.c $(SRC_DIR)/draw_utils.c $(SRC_DIR)/event.c \
	$(SRC_DIR)/color.c $(SRC_DIR)/convert_utils.c \
	$(SRC_DIR)/projection.c $(SRC_DIR)/projection_utils.c \
	$(SRC_DIR)/draw_banner.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIBFT_DIR)

LIBFT = -L$(LIBFT_DIR) -lft

# Détection automatique de l'OS
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
    # Configuration macOS
    LIBMLX_DIR = minilibx_mms_20200219
    MLX_LIB = $(LIBMLX_DIR)/libmlx.dylib
    CFLAGS += -I$(LIBMLX_DIR)
    MLX = -L$(LIBMLX_DIR) -lmlx -rpath @executable_path/$(LIBMLX_DIR) -framework Metal -framework MetalKit -framework Cocoa
endif

ifeq ($(UNAME_S), Linux)
    # Configuration Linux
    LIBMLX_DIR = libmlx
    MLX_LIB = $(LIBMLX_DIR)/libmlx.a
    CFLAGS += -I$(LIBMLX_DIR)
    MLX = -L$(LIBMLX_DIR) -lmlx -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MLX) $(LIBFT)

$(MLX_LIB):
	make -C $(LIBMLX_DIR)

$(LIBFT_DIR)/libft.a:
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
