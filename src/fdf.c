/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/28 18:04:26 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	print_map(int j, int i, t_malloc *data)
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

static	int	add_to_malloc_array(char *map, int ret, int fd, t_malloc *data)
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
	print_map(0, 0, data);
	return (0);
}



static int		find_xy(int fd, char *argv, t_malloc *data)
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
	/* printf("find x %d| %d| %d| %d| %d| %d| %d| last row is %d|\n", data->x[0], data->x[1], data->x[2], data->x[3],data->x[4], data->x[5], data->x[6], data->y);
	*/
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
/* 	char		**save; */
	t_malloc	data;

	/* save = (char**)malloc(sizeof(char*) * 100);
	*save = (char*)malloc(sizeof(char) * 100);
	data.map = *save; */
	i = 0;
	j = 0;
	ft_bzero(&data, sizeof(t_malloc));
	data.save = &map;
	find_xy(fd, map, &data);
/* 	find_y(fd, data); */

	return (0);
}


	/* while (map[i] != '\0')
	{
		i++;
		printf("first step %d %s\n", i, map);
	} */
