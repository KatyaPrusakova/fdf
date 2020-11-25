/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/25 13:56:53 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		manage_drawing(t_map *data)
{
	ft_bzero(data->p.buff, WIN_HEIGHT * WIN_WIDTH * 4);
	display_image(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
}

void			up_down_right_left(int key, t_map *data)
{
	if (key == DOWN)
		data->offset_y += 20;
	if (key == RIGHT)
		data->offset_x += 20;
	if (key == LEFT)
		data->offset_x -= 20;
	if (key == UP)
		data->offset_y -= 20;
}

int			ft_key(int key, t_map *data)
{
	if (key == 53)
		exit(0);
	if (key == DOWN || key == RIGHT || key == LEFT || key == UP)
		up_down_right_left(key, data);
	if (key == Q)
		data->projection = 1;
	if (key == W)
		data->projection = 0;
	if (key == 27)
	{
		if (data->zoom == 10)
			return (0);
		data->zoom -= 10;
	}
	if (key == 24)
		data->zoom += 10;
	if (key == X || key == Y || key == Z)
		data->rotation = key;
	manage_drawing(data);
	return (0);
}

void	adding_3d(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

void		rotate(float *x, float *y, t_map *data)
{
	float temp;

		temp = *y;
		
		*y = *y * cos(data->angle_x) + data->z * sin(data->angle_x);
		data->z = (-1 * temp) * sin(data->angle) + data->z * cos(data->angle_x);

		*x = *x * cos(data->angle) + data->z * sin(data->angle_y);
		data->z = (-1 * *x) * sin(data->angle) + data->z * cos(data->angle);

		*x = *x * cos(data->angle) - *y * sin(data->angle_z);
		*y = *x * sin(data->angle) + *y * cos(data->angle);
}

void		pixel_put(t_map *data, int x, int y, int color)
{
	int r;
	int g;
	int b;

	if (x <= 0 || y <= 0 || WIN_WIDTH <= x || WIN_HEIGHT <= y)
		return ;
	b = color % 256;
	g = color / 256 % 256;
	r = color / 256 / 256 % 256;
	data->p.buff[x * 4 + y * data->p.size_line] = r;
	data->p.buff[x * 4 + y * data->p.size_line + 1] = g;
	data->p.buff[x * 4 + y * data->p.size_line + 2] = b;
}

int			draw_line_pixel(t_map *data)
{
	float	max;
	float	step_x;
	float	step_y;
	int		color;

	color = data->z || data->z1 ? 0xe80c0c : 0x00FF00;
	step_x = data->print.x1 - data->print.x;
	step_y = data->print.y1 - data->print.y;
	max = MAX1(MOD(step_x), MOD(step_y));
	step_x /= max;
	step_y /= max;
	while ((int)(data->print.x - data->print.x1) || \
	(int)(data->print.y - data->print.y1))
	{
		pixel_put(data, data->print.x, data->print.y, color);
		data->print.x += step_x;
		data->print.y += step_y;
	}
	return (1);
}

void	zoom_in(t_map *data)
{
	data->print.x *= data->zoom;
	data->print.y *= data->zoom;
	data->print.x1 *= data->zoom;
	data->print.y1 *= data->zoom;
}

void			resize_img(t_map *data)
{
	data->print.x = data->c.x;
	data->print.y = data->c.y;
	data->print.x1 = data->c.x1;
	data->print.y1 = data->c.y1;
	zoom_in(data);
	if (!data->projection)
	{
		adding_3d(&data->print.x, &data->print.y, data->z, data->angle);
		adding_3d(&data->print.x1, &data->print.y1, data->z1, data->angle);
	}
	if (data->rotation)
	{
		rotate(&data->print.x, &data->print.y, data);
		rotate(&data->print.x1, &data->print.y1, data);
	}
	data->print.x += data->offset_x;
	data->print.y += data->offset_y;
	data->print.x1 += data->offset_x;
	data->print.y1 += data->offset_y;
	draw_line_pixel(data);
}

void			display_image(t_map *data)
{
	data->c.y = 0;
	while (data->c.y < data->y)
	{
		data->c.x = 0;
		while (data->c.x < data->x)
		{
			data->z = data->map[(int)data->c.y][(int)data->c.x];
			if (data->c.x + 1 < data->x)
			{
				data->c.x1 = data->c.x + 1;
				data->c.y1 = data->c.y;
				data->z1 = data->map[(int)data->c.y][(int)data->c.x1];
				resize_img(data);
			}
			if (data->c.y + 1 < data->y)
			{
				data->c.x1 = data->c.x;
				data->c.y1 = data->c.y + 1;
				data->z1 = data->map[(int)data->c.y1][(int)data->c.x];
				resize_img(data);
			}
			data->c.x++;
		}
		data->c.y++;
	}
}

void			mlx_info_display(t_map *data)
{
	mlx_string_put(data->p.mlx, data->p.win, 250, 20, 0xFFFFFF,\
	"Look at this amazing project");
}

int				fdf(int fd, char *map)
{
	t_map		data;

	ft_bzero(&data, sizeof(t_map));
	if (!(data.p.mlx = mlx_init()))
		return (0);
	data.p.win = mlx_new_window(data.p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF");
	data.p.image = mlx_new_image(data.p.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.p.buff = mlx_get_data_addr(data.p.image, &data.p.bits_per_pixel, \
	&data.p.size_line, &data.p.endian);
	mlx_key_hook(data.p.win, &ft_key, &data);
	mlx_info_display(&data);
	find_xy(fd, map, &data);
	data.offset_y = 300;
	data.offset_x = 300;
	data.zoom = 10;
	data.angle = 0.8;
	data.rotation = 0;
	manage_drawing(&data);
	mlx_loop(data.p.mlx);
	return (0);
}
