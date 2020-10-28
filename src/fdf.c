/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:49 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/28 12:00:03 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		find_x(int fd, t_malloc *data)
{
	int		ret;

	ret = 0;

	ret = get_next_line(fd, data->map);

		printf("x loop %d %d\n", data->x, ret);
		while (data->map[data->x] != '\0')
			data->x++;

	printf("find x %d %s\n", data->x, data->map[0]);
}

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

int		fdf(int fd, char *map)
{
	int			j;
	int			i;
/* 	char		**save; */
	t_malloc	*data;

	if (!(data = (t_malloc*)malloc(sizeof(t_malloc))))
		return (0);
	ft_bzero(data, sizeof(t_malloc));
	/* save = (char**)malloc(sizeof(char*) * 100);
	*save = (char*)malloc(sizeof(char) * 100);
	data.map = *save; */
	i = 0;
	j = 0;
	while (map[i] != '\0')
	{
		i++;
		printf("first step %d %s\n", i, map);
	}
	find_x(fd, data);
	find_y(fd, data);

	return (0);
}
