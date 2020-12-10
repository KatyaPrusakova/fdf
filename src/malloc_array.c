/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 11:55:23 by eprusako          #+#    #+#             */
/*   Updated: 2020/12/01 12:11:54 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_malloc_it(t_map *d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!(d->map = (int**)ft_memalloc(sizeof(int*) * (d->y))))
		print_error(3);
	while (j < d->y)
		d->map[j++] = (int*)ft_memalloc(sizeof(int) * d->x);
}

void		add_to_malloc_array(char *m, int len, int fd, t_map *d)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_malloc_it(d);
	while (get_next_line(fd, &m) > 0)
	{
		i = 0;
		len = 0;
		while (m[len] != '\0')
		{
			if (ft_isdigit(m[len]))
			{
				d->map[j][i] = len ? ft_atoi(&m[len - 1]) : ft_atoi(&m[len]);
				i++;
				while (ft_isdigit(m[len + 1]))
					len++;
			}
			len++;
		}
		j++;
		free(m);
	}
	manage_drawing(d);
}

void		find_xy(int fd, int j, char *argv, t_map *d)
{
	char	*m;
	int		i;

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
			if (m[i])
				i++;
		}
		d->y++;
		free(m);
	}
	d->x = j;
	close(fd);
	if ((fd = open(argv, O_RDONLY)) == -1)
		print_error(1);
	add_to_malloc_array(m, 0, fd, d);
}

void		check_x(char *str)
{
	int		j;
	int		i;
	int		fd;
	int		first;

	first = 0;
	i = 0;
	if ((fd = open(str, O_RDONLY)) == -1)
		print_error(1);
	while (get_next_line(fd, &str) > 0)
	{
		if (!first)
		{
			i = ft_strlen(str);
			first = 1;
		}
		j = ft_strlen(str);
		free(str);
	}
	if (i != j)
		print_error(3);
	close(fd);
}
