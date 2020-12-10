/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/12/10 14:00:37 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			pixel_put(t_map *d, int x, int y, int color)
{
	int r;
	int g;
	int b;

	if (x <= 0 || y <= 0 || WIN_WIDTH <= x || WIN_HEIGHT <= y)
		return ;
	b = color % 256;
	g = color / 256 % 256;
	r = color / 256 / 256 % 256;
	d->p.buff[x * 4 + y * d->p.size_line] = r;
	d->p.buff[x * 4 + y * d->p.size_line + 1] = g;
	d->p.buff[x * 4 + y * d->p.size_line + 2] = b;
}

int				draw_line_pixel(t_map *d)
{
	float	max;
	float	step_x;
	float	step_y;
	int		color;

	color = d->z ? 0xe80c0c : 0x00FF00;
	step_x = d->print.x1 - d->print.x;
	step_y = d->print.y1 - d->print.y;
	max = ft_abs(ft_mod(step_x), ft_mod(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(d->print.x - d->print.x1) || \
	(int)(d->print.y - d->print.y1))
	{
		pixel_put(d, d->print.x, d->print.y, color);
		d->print.x += step_x;
		d->print.y += step_y;
	}
	return (1);
}

void			resize_img(t_map *d)
{
	d->print.x = d->c.x;
	d->print.y = d->c.y;
	d->print.x1 = d->c.x1;
	d->print.y1 = d->c.y1;
	zoom_in(d);
	if (d->key)
	{
		rotate(&d->z, &d->print.y, d);
		rotate(&d->z1, &d->print.y1, d);
	}
	if (!d->projection)
	{
		adding_3d(&d->print.x, &d->print.y, d->z, d->angle);
		adding_3d(&d->print.x1, &d->print.y1, d->z1, d->angle);
	}
	d->print.x += d->offset_x;
	d->print.y += d->offset_y;
	d->print.x1 += d->offset_x;
	d->print.y1 += d->offset_y;
	draw_line_pixel(d);
}

void			display_image(t_map *d)
{
	d->c.y = 0;
	while (d->c.y < d->y)
	{
		d->c.x = 0;
		while (d->c.x < d->x)
		{
			d->z = d->map[(int)d->c.y][(int)d->c.x];
			if (d->c.x + 1 < d->x)
			{
				d->c.x1 = d->c.x + 1;
				d->c.y1 = d->c.y;
				d->z1 = d->map[(int)d->c.y][(int)d->c.x1];
				resize_img(d);
			}
			if (d->c.y + 1 < d->y)
			{
				d->c.x1 = d->c.x;
				d->c.y1 = d->c.y + 1;
				d->z1 = d->map[(int)d->c.y1][(int)d->c.x];
				resize_img(d);
			}
			d->c.x++;
		}
		d->c.y++;
	}
}

int				fdf(int fd, char *map)
{
	t_map		d;

	ft_bzero(&d, sizeof(t_map));
	if (!(d.p.mlx = mlx_init()))
		return (0);
	d.p.win = mlx_new_window(d.p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	d.p.image = mlx_new_image(d.p.mlx, WIN_WIDTH, WIN_HEIGHT);
	d.p.buff = mlx_get_data_addr(d.p.image, &d.p.bits_per_pixel, \
	&d.p.size_line, &d.p.endian);
	mlx_key_hook(d.p.win, &ft_key, &d);
	find_xy(fd, 0, map, &d);
	d.offset_y = 300;
	d.offset_x = 300;
	d.zoom = 10;
	d.angle = 0.8;
	d.key = 0;
	manage_drawing(&d);
	mlx_info(&d);
	mlx_loop(d.p.mlx);
	return (0);
}
