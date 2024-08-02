## ########################################################################## ##
##                                                                            ##
##                                                        :::      ::::::::   ##
##   Makefile                                           :+:      :+:    :+:   ##
##                                                    +:+ +:+         +:+     ##
##   By: uolle <uolle>                              +#+  +:+       +#+        ##
##                                                +#+#+#+#+#+   +#+           ##
##   Created: 2024/07/26 17:46:18 by uolle             #+#    #+#             ##
##   Updated: 2024/07/26 17:46:23 by uolle            ###   ########.fr       ##
##                                                                            ##
## ########################################################################## ##

HDRDIR   = includes
SRCDIR   = srcs
OBJDIR   = objs

SRCS     = srcs/get_next_line.c \
				   srcs/get_next_line_utils.c
OBJS     = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
NAME     = libget_next_line.a
CC       = cc
CFLAGS   = -Wall -Wextra -Werror
RM       = rm -rf
AR       = ar rcs

DEFCOLOR = \033[0;39m
GREEN    = \033[0;92m
YELLOW   = \033[0;93m
BLUE     = \033[0;94m
CYAN     = \033[0;96m

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)
	@echo "$(GREEN)get_next_line has been successfully compiled$(DEFCOLOR)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling: $< $(DEFCOLOR)"
	@$(CC) $(CFLAGS) -I $(HDRDIR) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@$(RM) $(OBJDIR)
	@echo "$(BLUE)get_next_line object files cleaned!$(DEFCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJDIR)
	@echo "$(CYAN)get_next_line executable has been cleaned!$(DEFCOLOR)"

re: fclean all
	@echo "$(GREEN)Cleaned and rebuilt successfully!$(DEFCOLOR)"

.PHONY: all clean fclean re
