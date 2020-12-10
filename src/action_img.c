/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:03:12 by eprusako          #+#    #+#             */
/*   Updated: 2020/12/01 00:30:11 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			adding_3d(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

void			rotate(int *z, float *y, t_map *d)
{
	float		yy;
	int			zz;

	yy = *y;
	zz = *z;
	if (d->key == LEFT_4 || d->key == RIGHT_6)
	{
		d->angle += d->key == LEFT_4 ? 0.3 : -0.3;
		*y = *y * cos(d->angle) + zz * sin(d->angle);
		*z = -yy * sin(d->angle) + zz * cos(d->angle);
	}
	d->key = 0;
	manage_drawing(d);
}

void			change_z(int j, int i, t_map *d)
{
	int			diff;

	diff = d->key == UP_8 ? 15 : -15;
	while (j < d->y)
	{
		i = 0;
		while (i < d->x)
		{
			if (d->map[j][i])
				d->map[j][i] += diff;
			i++;
		}
		j++;
	}
	d->key = 0;
}

void			zoom_in(t_map *d)
{
	d->print.x *= d->zoom;
	d->print.y *= d->zoom;
	d->print.x1 *= d->zoom;
	d->print.y1 *= d->zoom;
}

void			manage_drawing(t_map *d)
{
	ft_bzero(d->p.buff, WIN_HEIGHT * WIN_WIDTH * 4);
	display_image(d);
	mlx_put_image_to_window(d->p.mlx, d->p.win, d->p.image, 0, 0);
	mlx_info(d);
}
