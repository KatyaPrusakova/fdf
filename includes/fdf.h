/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:39:09 by eprusako          #+#    #+#             */
/*   Updated: 2020/12/10 13:58:35 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

# define BUF		1000
# define WIN_HEIGHT	1000
# define WIN_WIDTH	1000

# define Z_IN		61
# define Z_OUT		45
# define UP			65362
# define DOWN		65364
# define RIGHT		65363
# define LEFT		65361
# define Q			113
# define W			119
# define UP_8		65464
# define DOWN_2		65458
# define LEFT_4		65462
# define RIGHT_6	65460
# define ESC		65307

typedef	struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*image;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	char			*buff;
}					t_mlx;

typedef	struct		s_point
{
	float			x;
	float			y;
	float			x1;
	float			y1;
}					t_point;

typedef	struct		s_pix
{
	float			x;
	float			y;
	float			x1;
	float			y1;
}					t_pix;

typedef	struct		s_map
{
	int				**map;
	int				x;
	int				y;
	int				z;
	int				z1;
	int				offset_x;
	int				offset_y;
	int				zoom;
	int				projection;
	float			angle;
	int				key;
	t_mlx			p;
	t_point			c;
	t_pix			print;
}					t_map;

/*
** ------ FDF.C ------
*/

int					fdf(int fd, char *map);
void				display_image(t_map *d);
void				resize_img(t_map *d);
int					draw_line_pixel(t_map *d);
void				pixel_put(t_map *d, int x, int y, int color);

/*
** ------ MAIN.C ------
*/

int					ft_key(int key, t_map *d);
void				up_down_right_left(int key, t_map *d);
void				mlx_info(t_map *d);
int					print_error(int n);

/*
** ------ MALLOC_ARRAY.C ------
*/

void				find_xy(int fd, int j, char *argv, t_map *d);
void				add_to_malloc_array(char *m, int len, int fd, t_map *d);
void				check_x(char *str);
void				ft_malloc_it(t_map *d);

/*
** ------ ACTION_IMG.C ------
*/

void				rotate(int *z, float *y, t_map *d);
void				change_z(int j, int i, t_map *d);
void				adding_3d(float *x, float *y, int z, float angle);
void				zoom_in(t_map *d);
void				manage_drawing(t_map *d);

#endif
