/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:31:44 by eprusako          #+#    #+#             */
/*   Updated: 2020/12/10 14:01:10 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				print_error(int n)
{
	if (n == 0)
		write(1, "usage ./fdf map.fdf\n", 21);
	if (n == 1)
		write(1, "error: file open failed\n", 25);
	if (n == 2)
		write(1, "error: too much arguments\n", 27);
	if (n == 3)
		write(1, "error: wrong map\n", 18);
	if (n == 4)
		write(1, "error: malloc fail\n", 20);
	exit(0);
}

int				main(int argc, char **argv)
{
	int fd;

	if (argc == 1)
		print_error(0);
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) == -1)
			print_error(1);
		fdf(fd, argv[1]);
	}
	if (argc > 2)
		print_error(2);
}

void			mlx_info(t_map *d)
{
	mlx_string_put(d->p.mlx, d->p.win, 20, 10, 0xFFFFFF,
	"Use direction keys to move the map");
	mlx_string_put(d->p.mlx, d->p.win, 20, 30, 0xFFFFFF,
	"Q and W to change perspective");
	mlx_string_put(d->p.mlx, d->p.win, 20, 50, 0xFFFFFF,
	"+ and - to zoom in and out");
	mlx_string_put(d->p.mlx, d->p.win, 20, 70, 0xFFFFFF,
	"8 and 2 to change z values");
	mlx_string_put(d->p.mlx, d->p.win, 20, 90, 0xFFFFFF,
	"4 and 6 to change the angle");
}

void			up_down_right_left(int key, t_map *d)
{
	if (key == DOWN)
		d->offset_y += 20;
	if (key == RIGHT)
		d->offset_x += 20;
	if (key == LEFT)
		d->offset_x -= 20;
	if (key == UP)
		d->offset_y -= 20;
}

int				ft_key(int key, t_map *d)
{
	if (key == ESC)
		exit(0);
	if (key == DOWN || key == RIGHT || key == LEFT || key == UP)
		up_down_right_left(key, d);
	if (key == Q)
		d->projection = 1;
	if (key == W)
		d->projection = 0;
	if (key == Z_OUT)
	{
		if (d->zoom == 10)
			return (0);
		d->zoom -= 10;
	}
	if (key == Z_IN)
		d->zoom += 10;
	if (key == UP_8 || key == DOWN_2)
	{
		d->key = key;
		change_z(0, 0, d);
	}
	if (key == LEFT_4 || key == RIGHT_6)
		d->key = key;
	manage_drawing(d);
	return (0);
}
