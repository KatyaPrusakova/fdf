/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:10 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/31 12:18:25 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


#include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# include "../libft/libft.h"



# define BUF 1000
# define WIN_HEIGHT	1000
# define WIN_WIDTH	1000
#define MAX1(a, b) (a > b ? a : b)
#define MOD(a) (a < 0 ? -a : a)



# define Z_IN	27
# define Z_OUT	24
# define UP		126
# define DOWN	125
# define RIGHT	124
# define LEFT	123

typedef	struct		s_mlx
{
	void		*mlx;
	void		*win;
	void		*image;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	char		*buff;
}					t_mlx;

typedef	struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef	struct		s_map
{
	int		**map;
	int			x;
	int			y;
	int			z;
	int			z1;
	int			offset_x;
	int			offset_y;
	int			zoom;
	t_mlx		p;
	t_point		*point;
}					t_map;



int		fdf(int fd, char *map);
int		find_xy(int fd, char *argv, t_map *data);

int		open_map(t_map *data);
void	display_map(t_map *data);
void	print_map(int j, int i, t_map *data);


int		add_to_malloc_array(char *map, int fd, t_map *data);


void		manage_drawing(t_map *data);
#endif

