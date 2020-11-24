/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:55:23 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/06 12:25:51 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			add_to_malloc_array(char *map, int fd, t_map *data)
{
	int		i = 0;
	int		j = 0;
	int		len = 0;


	if (!(data->map = (int**)ft_memalloc(sizeof(int*) * (data->y))))
		return (0);
	while (j < data->y)
		data->map[j++] = (int*)ft_memalloc(sizeof(int) * data->x);
	j = 0;
	while (get_next_line(fd, &map) > 0)
	{
		i = 0;
		len = 0;
		while (map[len] != '\0')
		{
			if (ft_isdigit(map[len]))
			{
				data->map[j][i] = len ? ft_atoi(&map[len-1]) : ft_atoi(&map[len]);
				i++;
				while (ft_isdigit(map[len+1]))
					len++;
			}
			len++;
		}
		j++;
		free(map);
	}
	print_map(0, 0, data);
	manage_drawing(data);
	return (0);
}

int			find_xy(int fd, char *argv, t_map *data)
{
	char	*m;
	int		i;
	int		j;

	m = argv;
	while (get_next_line(fd, &m) > 0)
	{
		i = 0;
		j = 0;
		while (m[i] != '\0')
		{
			if (ft_isdigit(m[i]))
				j++;
			while (ft_isdigit(m[i]))
					i++;
		i++;
		}
		data->y++;
		free(m);
	}
	data->x = j;
	close(fd);
	fd = open(argv, O_RDONLY);
	add_to_malloc_array(m, fd, data);
	return (1);
}

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