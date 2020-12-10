# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/15 11:04:15 by eprusako          #+#    #+#              #
#    Updated: 2020/12/10 13:58:03 by eprusako         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = ./libft/
DIR_SRC = src
HEADER = -I includes/ -I minilibx2/
MLX = -L /usr/local/lib -lmlx -I /usr/local/X11/include -L/usr/X11/lib -lX11 -lXext -framework OpenGL -framework Appkit

SRC = fdf.c main.c malloc_array.c action_img.c

YELLOW = "\033[1;33m"
NOCOLOR = "\033[0m"

SRCS = $(addprefix $(DIR_SRC)/, $(SRC))
OBJS=$(notdir $(SRCS:.c=.o))

all: $(NAME)

$(NAME):
	@echo $(YELLOW)Compiling FDF...$(NOCOLOR)
	@make -C $(LIBFT)
	@gcc -Wall -Wextra -Werror -c $(SRCS) $(HEADER)
	@gcc -g $(HEADER) $(OBJS) libft/libft.a $(MLX) -o $(NAME)

clean:
	@echo $(YELLOW)Cleaning...$(NOCOLOR)
	@/bin/rm -rf $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@echo $(YELLOW)F-cleaning...$(NOCOLOR)
	@/bin/rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: $(NAME), all, clean, fclean, re
