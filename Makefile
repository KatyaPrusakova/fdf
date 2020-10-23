# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 11:04:15 by eprusako          #+#    #+#              #
#    Updated: 2020/10/23 11:37:52 by eprusako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = ./libft
LIBFTFLAGS= -L$(LIBFT) -lft
DIR_SRC = src
DIR_OBJ = obj_dir
HEADER = includes

MAIN =	main.c
SRC =	fdf.c

YELLOW = "\033[1;33m"
NOCOLOR = "\033[0m"

SRCS = $(addprefix $(DIR_SRC)/, $(SRC))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJS)
	@echo $(YELLOW)Compiling libftprintf.a...$(NOCOLOR)
	@make -C $(LIBFT)
	gcc -g $(NAME) $(MAIN)


$(DIR_OBJ):
	@echo $(YELLOW)Compiling to .o files...$(NOCOLOR)
	@mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c $(HEADER)/fdf.h
	@gcc -g -Wall -Wextra -Werror -I$(HEADER) -c -o $@ $<

clean:
	@echo $(YELLOW)Cleaning...$(NOCOLOR)
	@/bin/rm -rf $(DIR_OBJ)
	@make -C $(LIBFT) clean

fclean: clean
	@echo $(YELLOW)F-cleaning...$(NOCOLOR)
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: $(NAME), all, clean, fclean, re
