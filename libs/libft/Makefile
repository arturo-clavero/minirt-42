## ########################################################################## ##
##                                                                            ##
##                                                        :::      ::::::::   ##
##   Makefile                                           :+:      :+:    :+:   ##
##                                                    +:+ +:+         +:+     ##
##   By: uolle <uolle>                              +#+  +:+       +#+        ##
##                                                +#+#+#+#+#+   +#+           ##
##   Created: 2024/07/26 17:46:31 by uolle             #+#    #+#             ##
##   Updated: 2024/07/26 17:46:32 by uolle            ###   ########.fr       ##
##                                                                            ##
## ########################################################################## ##

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = includes

SRC_FILES = $(SRC_DIR)/file/ft_putchar_fd.c \
            $(SRC_DIR)/file/ft_putendl_fd.c \
            $(SRC_DIR)/file/ft_putnbr_fd.c \
            $(SRC_DIR)/file/ft_putstr_fd.c \
            $(SRC_DIR)/mem/ft_bzero.c \
            $(SRC_DIR)/mem/ft_calloc.c \
            $(SRC_DIR)/mem/ft_memchr.c \
            $(SRC_DIR)/mem/ft_memcmp.c \
            $(SRC_DIR)/mem/ft_memcpy.c \
            $(SRC_DIR)/mem/ft_memmove.c \
            $(SRC_DIR)/mem/ft_memset.c \
            $(SRC_DIR)/misc/ft_isalnum.c \
            $(SRC_DIR)/misc/ft_isalpha.c \
            $(SRC_DIR)/misc/ft_isascii.c \
            $(SRC_DIR)/misc/ft_isdigit.c \
            $(SRC_DIR)/misc/ft_isprint.c \
            $(SRC_DIR)/misc/ft_ispsace.c \
            $(SRC_DIR)/nbr/ft_atoi.c \
            $(SRC_DIR)/nbr/ft_itoa.c \
            $(SRC_DIR)/nbr/ft_atof.c \
            $(SRC_DIR)/str/ft_split.c \
            $(SRC_DIR)/str/ft_strchr.c \
            $(SRC_DIR)/str/ft_strcmp.c \
            $(SRC_DIR)/str/ft_strdup.c \
            $(SRC_DIR)/str/ft_striteri.c \
            $(SRC_DIR)/str/ft_strjoin.c \
            $(SRC_DIR)/str/ft_strlcat.c \
            $(SRC_DIR)/str/ft_strlcpy.c \
            $(SRC_DIR)/str/ft_strlen.c \
            $(SRC_DIR)/str/ft_strmapi.c \
            $(SRC_DIR)/str/ft_strncmp.c \
            $(SRC_DIR)/str/ft_strnstr.c \
            $(SRC_DIR)/str/ft_strrchr.c \
            $(SRC_DIR)/str/ft_strtrim.c \
            $(SRC_DIR)/str/ft_substr.c \
            $(SRC_DIR)/str/ft_tolower.c \
            $(SRC_DIR)/str/ft_toupper.c \
            $(SRC_DIR)/str/ft_trim.c

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC_FLAGS = -I $(INC_DIR)

NAME = libft.a

AR = ar rcs
RM = rm -rf
MKDIR = mkdir -p

RESET = \033[0m
BLUE = \033[0;94m
GREEN = \033[0;92m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $@ $^
	@echo "$(GREEN)[OK] - Libft has been created successfully.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	@$(MKDIR) $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@
	@echo "$(BLUE)[INFO] - Compiling: $<$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)[OK] - Object files have been removed.$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)[OK] - Libft has been removed correctly.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

