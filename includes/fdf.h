/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:10 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/30 12:01:56 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


#include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>

# include "../libft/libft.h"


# define BUF 1000
# define WIN_HEIGHT	800
# define WIN_WIDTH	900

typedef	struct		s_malloc
{
	int		**map;
	char	**save;
	int			x[BUF];
	int			y;
	int			r;
}					t_malloc;

typedef	struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

int		fdf(int fd, char *map);

#endif
