/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 10:31:44 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/25 11:24:48 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	print_error(int n)
{
	if (n == 0)
		write(1, "usage ./fdf map.fdf\n", 21);
	if (n == 1)
		write(1, "error: file open failed\n", 25);
	if (n == 2)
		write(1, "error: too much arguments\n", 27);
	if (n == 3)
		write(1, "error: malloc failed\n", 22);
	exit (0);
}

int		main(int argc, char **argv)
{
	int fd;

	if (argc == 1)
		print_error(0);
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 1)
			print_error(1);
		fdf(fd, argv[1]);
	}
	if (argc > 2)
		print_error(2);
}
