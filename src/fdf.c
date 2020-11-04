/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/04 19:39:41 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	int loop_it(t_map *data);

static	void	print_map(int j, int i, t_map *data)
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
}

/* void		manage_drawing(t_map *data)
{
	ft_bzero(data->p.buff, WIN_HEIGHT * WIN_WIDTH);
	loop_it(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
} */

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
	draw_background(data);
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
		pixel_put(data, x, y, color); // mlx_
		x += step_x;
		y += step_y;
	}
	return (1);
}

/* static	int	draw_line_pixel(void *mlx, void *win, float start_x, float start_y, float end_x, float end_y)
{
	float k;
	float y;
	float new_x;
	float new_y;

	start_x *=20;
	start_y *=20;
	end_x *=20;
	end_y *=20;
	y = start_y;
	new_x = end_x - start_x;
	new_y = end_y - start_y;
	k = new_x / new_y;

	while (start_x < end_x)
	{
		mlx_pixel_put(mlx, win, start_x, start_y, 0x00FF00);
		start_y = start_y + k;
		start_x++;
	}
	return (1);
} */

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

static	void mlx_info_display(t_map *data)
{
	mlx_string_put(data->p.mlx, data->p.win, 250, 20, 0xFFFFFF,"Look at this amazing project");
}

static	int	open_map(t_map *data)
{
	if (!(data->p.mlx = mlx_init()))
		return (0);
	data->p.win = mlx_new_window(data->p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF PROJECT");
	mlx_key_hook(data->p.win, &ft_key, &data);

	data->p.image = mlx_new_image(data->p.mlx, WIN_WIDTH, WIN_HEIGHT);
	data->p.buff = mlx_get_data_addr(data->p.image, &data->p.bits_per_pixel, &data->p.size_line, &data->p.endian);
	mlx_info_display(data);
	loop_it(data);
	mlx_put_image_to_window(data->p.mlx, data->p.win, data->p.image, 0, 0);
	mlx_loop(data->p.mlx);
	return (0);
}


static	int	add_to_malloc_array(char *map, int ret, int fd, t_map *data)
{
	int		i = 0;
	int		j = 0;
	int		len = 0;


	if (!(data->map = (int**)ft_memalloc(sizeof(int*) * (data->y))))
		return (0);
	while (j < data->y)
		data->map[j++] = (int*)ft_memalloc(sizeof(int) * data->x);
	j = 0;
	while ((ret = get_next_line(fd, &map)) > 0)
	{
		i = 0;
		len = 0;
		while (map[len] != '\0')
		{
			if (ft_isdigit(map[len]))
			{
				data->map[j][i] = ft_atoi(&map[len]);
				i++;
				while (ft_isdigit(map[len+1]))
                    len++;
			}
			len++;
		}
		j++;
		free(map);
	}
	open_map(data);
	print_map(0, 0, data);
	return (0);
}

static int		find_xy(int fd, char *argv, t_map *data)
{
	char	*m;
	int		ret;
	int		i;
	int		j;

	m = argv;
	while ((ret = get_next_line(fd, &m)) > 0)
	{
		i = 0;
		j = 0;
		while (m[i] != '\0')
		{
			if (ft_isdigit(m[i]))
				j++;
			i++;
		}
		data->y++;
		free(m);
	}
	data->x = j;
	close(fd);
	fd = open(argv, O_RDONLY);
	add_to_malloc_array(m, 0, fd, data);
	return (1);
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

