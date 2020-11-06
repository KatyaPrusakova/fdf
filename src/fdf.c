/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/06 12:34:53 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int loop_it(t_map *data);
void display_map(t_map *data);

void	print_map(int j, int i, t_map *data)
{
	while (j < data->y)
	{
		i = 0;
		while (i < data->x)
		{
			printf("%d ", data->map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

void	move_it_with_key(int key, t_map *data)
{
	if (key == 0)
		data->offset -= 20;
	if (key == 1)
		data->offset += 20;
	if (key == 2)
		data->offset += 20;
	if (key == 3)
		data->offset -= 20;
	manage_drawing(data);
}

void		manage_drawing(t_map *data)
{
	ft_bzero(data->p.buff, WIN_HEIGHT * WIN_WIDTH * 4);
	loop_it(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
}

void	draw_background(t_map *data)
{
	int i;

	i = 0;
	while (i < WIN_WIDTH * WIN_HEIGHT * 4)
	{
		data->p.buff[i] = (char)32;
		data->p.buff[i + 1] = (char)32;
		data->p.buff[i + 2] = (char)32;
		i += 4;
	}
}

static int	ft_key(int key, t_map *data)
{
	ft_putnbr(key);
	printf("\n");

	if (key == 53)
		exit(0);
	if (key >= 123 && key <= 126)
	{
		move_it_with_key(126 - key, data);
	}
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

 static	void	adding_3d( float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;
}

static	void	zoom_in( float *x, float *y, float *x1, float *y1)
{
	*x *=20;
	*y *=20;
	*x1 *=20;
	*y1 *=20;
}


static	void pixel_put(t_map *data, int x, int y, int color)
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

static	int	draw_line_pixel(t_map *data, float x, float y, float x1, float y1)
{
	float max;
	float step_x;
	float step_y;
	int		color;

	data->z = data->map[(int)y][(int)x];
	data->z1 = data->map[(int)y1][(int)x1];
	data->offset = 300;
	color = data->z ? 0xe80c0c : 0x00FF00;
	zoom_in(&x, &y, &x1, &y1);

	adding_3d(&x, &y, data->z, 0.8);
	adding_3d(&x1, &y1, data->z1, 0.8);

	x += data->offset;
	y += data->offset;
	x1 += data->offset;
	y1 += data->offset;

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

static	int loop_it(t_map *data)
{
	int i;
	int j;

	j = 0;
	while (j < data->y)
	{
		i = 0;
		while (i < data->x)
		{
			if (i+1 < data->x)
				draw_line_pixel(data, i, j, i+1, j);
			if (j+1 < data->y)
				draw_line_pixel(data, i, j, i, j+1);
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

void display_map(t_map *data)
{
	loop_it(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
}

int		open_map(t_map *data)
{
	if (!(data->p.mlx = mlx_init()))
		return (0);
	data->p.win = mlx_new_window(data->p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF PROJECT");
	mlx_key_hook(data->p.win, &ft_key, &data);
	data->p.image = mlx_new_image(data->p.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->p.buff = mlx_get_data_addr(data->p.image, &data->p.bits_per_pixel, &data->p.size_line, &data->p.endian);
	mlx_info_display(data);
	display_map(data);

	mlx_loop(data->p.mlx);
	return (0);
}

int		fdf(int fd, char *map)
{
	int			j;
	int			i;
	t_map		data;

	i = 0;
	j = 0;
	ft_bzero(&data, sizeof(t_map));
	find_xy(fd, map, &data);
	return (0);
}

