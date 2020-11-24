/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/31 13:57:15 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		manage_drawing(t_map *data)
{
	ft_bzero(data->p.buff, WIN_HEIGHT * WIN_WIDTH * 4);
	loop_it(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
}

static int	ft_key(int key, t_map *data)
{
	ft_putnbr(key);
	printf("\n");

	if (key == 53)
		exit(0);
	if (key == DOWN)
		data->offset_y += 20;
	if (key == RIGHT)
		data->offset_x += 20;
	if (key == LEFT)
		data->offset_x -= 20;
	if (key == UP)
		data->offset_y -= 20;

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
	manage_drawing(data);
	return (0);
}

void	adding_3d( float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

void	zoom_in( float *x, float *y, float *x1, float *y1, t_map *data)
{
	*x *= data->zoom;
	*y *= data->zoom;
	*x1 *= data->zoom;
	*y1 *= data->zoom;
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

int			draw_line_pixel(t_map *data, float x, float y, float x1, float y1)
{
	float	max;
	float	step_x;
	float	step_y;
	int		color;

	color = data->z || data->z1 ? 0xe80c0c : 0x00FF00;

	step_x = x1 - x;
	step_y = y1 - y;
	max = MAX1(MOD(step_x), MOD(step_y));
	step_x /= max;
	step_y /=max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		pixel_put(data, x, y, color);
		x += step_x;
		y += step_y;
	}
	return (1);
}

void			draw_line_pixel_change(t_map *data, float x, float y, float x1, float y1)
{
	zoom_in(&x, &y, &x1, &y1, data);

	if (!data->projection) {
		adding_3d(&x, &y, data->z, 0.8);
		adding_3d(&x1, &y1, data->z1, 0.8);
	}
	x += data->offset_x;
	y += data->offset_y;
	x1 += data->offset_x;
	y1 += data->offset_y;

	draw_line_pixel(data, x, y, x1, y1);
}

int			loop_it(t_map *data)
{
	int		i;
	int		j;

	j = 0;
	while (j < data->y)
	{
		i = 0;
		while (i < data->x)
		{
			if (i+1 < data->x)
			{
				data->z = data->map[(int)j][(int)i];
				data->z1 = data->map[(int)j][(int)i + 1];
				draw_line_pixel_change(data, i, j, i+1, j);
			}
			if (j+1 < data->y)
			{
				data->z = data->map[(int)j][(int)i];
				data->z1 = data->map[(int)j+1][(int)i];
				draw_line_pixel_change(data, i, j, i, j+1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void mlx_info_display(t_map *data)
{
	mlx_string_put(data->p.mlx, data->p.win, 250, 20, 0xFFFFFF,"Look at this amazing project");
}

int		fdf(int fd, char *map)
{
	t_map		data;

	ft_bzero(&data, sizeof(t_map));
 	if (!(data.p.mlx = mlx_init()))
		return (0);
	data.p.win = mlx_new_window(data.p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF PROJECT");
	data.p.image = mlx_new_image(data.p.mlx, WIN_WIDTH, WIN_HEIGHT);
	data.p.buff = mlx_get_data_addr(data.p.image, &data.p.bits_per_pixel, &data.p.size_line, &data.p.endian);
	mlx_key_hook(data.p.win, &ft_key, &data);
	mlx_info_display(&data);
	find_xy(fd, map, &data);
	data.offset_y = 300;
	data.offset_x = 300;
	data.zoom = 10;
	manage_drawing(&data);
	mlx_loop(data.p.mlx);
	return (0);
}


/*
static int	ft_key_mouse(int key)
{
	ft_putnbr(key);
	printf("\n");
	if (key == 1)
		return (1);
	if (key == 1)
		return (2);
	if (key == 5)
		printf("\n");
	if (key == 4)
		printf("\n");
	return (0);
}
 */

/*
static	int	draw_line(void *mlx, void *win, float end_x, float end_y)
{
	int start_x = 400;
	int start_y = 400;
	int new_x = start_x;
	int new_y = start_y;
	void *image = mlx_new_image(mlx, new_x, new_y);
	end_x = start_x + end_x;
 	end_y = start_y + end_y;
	int pixel_bits;
	int line_pixels;
	int endian;
	int color = 0xABCDEF;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_pixels, &endian);
	while (start_y < end_y)
	{
		while ( start_x < end_x)
			{
				int pixel = (start_y * line_pixels) + (start_x * 4);
				buffer[pixel + 0] = (color) & 0xFF;
				buffer[pixel + 1] = (color >> 8) & 0xFF;
				buffer[pixel + 2] = (color >> 16) & 0xFF;
				buffer[pixel + 3] = (color >> 24);
				++start_x;
			}
		++start_y;
	}
	mlx_put_image_to_window(mlx, win, image, 400, 400);
	return (0);
}
 */