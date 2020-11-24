# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 11:04:15 by eprusako          #+#    #+#              #
#    Updated: 2020/10/30 16:51:10 by eprusako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = ./libft
LIBFTFLAGS= -L ./minilibx -lmlx -L$(LIBFT) -lft
DIR_SRC = src
DIR_OBJ = obj_dir
HEADER = -I includes/ -I minilibx2/
FRAMEWORK = -framework OpenGL -framework AppKit
# MLX=-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL \
# -framework Appkit

SRC =	fdf.c main.c malloc_array.c

YELLOW = "\033[1;33m"
NOCOLOR = "\033[0m"

SRCS = $(addprefix $(DIR_SRC)/, $(SRC))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(DIR_OBJ) $(OBJS) 
	@echo $(YELLOW)Compiling FDF...$(NOCOLOR)
	@make -C $(LIBFT)
	@gcc -g $(HEADER) fdf.o main.o malloc_array.o libft/libft.a -L /usr/local/lib -lmlx -I /usr/local/X11/include -L/usr/X11/lib -lX11 -lXext -framework OpenGL -framework Appkit -o $(NAME)


$(DIR_OBJ):
	@echo $(YELLOW)Compiling to .o files...$(NOCOLOR)
	@mkdir $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c
	@gcc -Wall -Wextra -Werror  -c $(SRCS) $(HEADER)

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
