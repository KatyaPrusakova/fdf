/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/04 12:59:27 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX1(a, b) (a > b ? a : b)

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

static int	ft_key(int key)
{
	ft_putnbr(key);
	printf("\n");

	if (key == 53)
		exit(0);
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
/* static	int	draw_line_pixel(void *mlx, void *win, float start_x, float start_y, float end_x, float end_y)
{
	float max;

	float step_x;
	float step_y;

	start_x *=20;
	start_y *=20;
	end_x *=20;
	end_y *=20;
	step_x = end_x - start_x;
	step_y = end_y - start_y;
	max = MAX1(step_x, step_y);
	step_x /= max;
	step_y /=max;

	while ((int)(start_x - end_x) || (int)(start_y - end_y))
	{
		mlx_pixel_put(mlx, win, start_x, start_y, 0x00FF00);

		start_x += step_x;
		start_y += step_y;
	}
	return (1);
} */

static	int	draw_line_pixel(void *mlx, void *win, float start_x, float start_y, float end_x, float end_y)
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
		/* printf("%f %f \n", start_x, start_y); */
		start_y = start_y + k;
		start_x++;
	}
	return (1);
}


static	int loop_it(t_mlx p, t_map *data)
{
	int i;
	int j = 0;

	while (j < data->y)
	{
		i = 0;
		while (i < data->x)
		{
			if (i+1 < data->x)
				draw_line_pixel(p.mlx, p.win, i, j, i+1, j);
			if (j+1 < data->y)
				draw_line_pixel(p.mlx, p.win, i, j, i, j+1);
			i++;
		}
		j++;
	}
	return (0);
}

static	int	open_map(t_map *data)
{
	t_mlx	p;

	data->r = data->r + 0;
	ft_bzero(&p, sizeof(t_mlx));
	if (!(p.mlx = mlx_init()))
		return (0);
	p.win = mlx_new_window(p.mlx, WIN_WIDTH, WIN_HEIGHT, "FDF PROJECT");

	mlx_key_hook(p.win, &ft_key, data);
	mlx_string_put(p.mlx, p.win, 250, 20, 0xFFFFFF,"This shit will never work");
/* 	draw_line(p.mlx, p.win, data->x, data->y); */
	loop_it(p, data);
	/* draw_line_pixel(p.mlx, p.win, data->x, data->y, 400 + data->x, 400 + data->y); */
	mlx_loop(p.mlx);
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
	}
	print_map(0, 0, data);
	open_map(data);
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

