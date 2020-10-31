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

static	void	print_map(int j, int i, t_map *data)
{
	int x;

	x = 0;
	while (j < data->y)
	{
		i = 0;
		while (i < data->x[x])
		{
			printf("%d ", data->map[j][i]);
			i++;
		}
		printf("\n");
		j++;
		x++;
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

static int	ft_key_mouse(int key, t_map *data)
{
	ft_putnbr(key);
	printf("\n");

	data->r = data->r + 0;
	if (key == 5) /* mouse zoom in (re drawing ) */
		printf("\n");
	if (key == 4) /* mouse zoom out (re drawing ) */
		printf("\n");
	return (0);
}

static	int	draw_line(void *mlx, void *win, float end_x, float end_y)
{
	float k;
	float y;
	float start_x = 400;
	float start_y = 400;
	float new_x = start_x;
	float new_y = start_y;

	end_x = start_x + end_x;
 	end_y = start_y + end_y * -1;

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
	return (0);
}

static	int	get_new_xyz(t_map *data)
{
	/* draw_line(p.mlx, p.win, data->x[x], s); */
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
	mlx_mouse_hook(p.win, &ft_key_mouse, data);

	get_new_xyz(data);

	mlx_loop(p.mlx);
	return (0);
}

static	int	add_to_malloc_array(char *map, int ret, int fd, t_map *data)
{
	int		i = 0;
	int		j = 0;


	if (!(data->map = (int**)malloc(sizeof(int*) * (data->y))))
		return (0);
	while (j < data->y)
		data->map[j++] = (int*)malloc(sizeof(int) * data->x[i++]);
	j = 0;
	while ((ret = get_next_line(fd, &map)) > 0)
	{
		i = 0;
		data->r = 0;
		while (map[i] != '\0')
		{
			if (ft_isdigit(map[i]))
			{
				data->map[j][data->r] = ft_atoi(&map[i]);
				data->r++;
				while (ft_isdigit(map[i+1]))
					i++;
			}
			i++;
		}
		j++;
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
		j = 0;
		i = 0;
		while (m[i] != '\0')
		{
			if (ft_isdigit(m[i]))
			{
				j++;
				while (ft_isdigit(m[i+1]))
					i++;
			}
			i++;
		}
		data->x[data->y] = j;
		data->y++;
	}
	close(fd);
	fd = open(argv, O_RDONLY);
	add_to_malloc_array(m, 0, fd, data);
	return (1);
}


/*
static void		find_y(int fd, t_malloc *data)
{
	int		ret;

	ret = 0;
	while (ret == get_next_line(fd, data->map))
	{
		printf("y loop %d %d\n", data->y, ret);
		data->y++;
	}
	printf("find y %d %s\n", data->y, data->map[data->y]);
}
 */

int		fdf(int fd, char *map)
{
	int			j;
	int			i;
	t_map	data;

	i = 0;
	j = 0;
	ft_bzero(&data, sizeof(t_map));
	find_xy(fd, map, &data);
/* 	find_y(fd, data); */

	return (0);
}


	/* while (map[i] != '\0')
	{
		i++;
		printf("first step %d %s\n", i, map);
	} */
