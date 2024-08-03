# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: artclave <artclave@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 17:46:08 by uolle             #+#    #+#              #
#    Updated: 2024/08/03 16:58:10 by artclave         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CPPFLAGS = -Iincludes -Isrc -Ilibs/get_next_line/includes -Ilibs/libft/includes
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
LDLIBS = -lm
LIB_DIR = libs

SRC = src
OBJ = obj
BIN = miniRT

SRCS = src/lexer/adds.c \
       src/lexer/main.c \
       src/lexer/utils.c \
			 src/matrix/matrix_inversion.c \
       src/matrix/matrix_op.c \
       src/matrix/matrix_utils.c \
       src/matrix/tranform.c \
       src/parsing/add_light.c \
			 src/parsing/add_other.c \
       src/parsing/error.c \
       src/parsing/main.c \
       src/parsing/utils.c \
			 src/parsing/utils_2.c \
			 src/render/camera.c \
			 src/render/light.c \
			 src/render/light_utils.c \
			 src/render/ray.c \
			 src/render/scene.c \
			 src/render/shape.c \
			 src/utils/clean.c \
			 src/utils/hook.c \
			 src/utils/mlx_utils.c \
			 src/vectors/math_utils.c \
       src/vectors/vector_math.c \
       src/vectors/vector_op.c \
       src/vectors/vector_utils.c \
			 src/main.c

HEADERS = includes/camera.h \
          includes/lexer.h \
					includes/light.h \
          includes/matrix.h \
					includes/mlx_utils.h \
          includes/parsing.h \
		  includes/debug.h \
					includes/ray.h \
					includes/scene.h \
					includes/shapes.h \
					includes/vector.h \
					includes/header.h

LIBFT_DIR = libs/libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

GNL_DIR = libs/get_next_line
GNL_LIB = $(GNL_DIR)/libget_next_line.a

LIBS = -L$(LIB_DIR) -lmlx_Linux -lXext -lX11 -lm -lbsd -L$(GNL_DIR) -lget_next_line -L$(LIBFT_DIR) -lft
MKDIR = mkdir -p

OBJS = $(SRCS:$(SRC)/%.c=$(OBJ)/%.o)

all: $(LIBFT_LIB) $(GNL_LIB) $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LIBS) -o $@ $(LDLIBS)

$(OBJ)/%.o: $(SRC)/%.c $(HEADERS)
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(GNL_LIB):
	$(MAKE) -C $(GNL_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) -R $(BIN)
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) -R $(OBJ)
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
