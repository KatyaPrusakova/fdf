/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:39:10 by eprusako          #+#    #+#             */
/*   Updated: 2020/11/04 16:18:00 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H


#include <stdio.h>

# include <stdlib.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

# include "../libft/libft.h"


# define BUF 1000
# define WIN_HEIGHT	800
# define WIN_WIDTH	900

typedef	struct		s_mlx
{
	void		*mlx;
	void		*win;
}					t_mlx;

typedef	struct		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef	struct		s_map
{
	int		**map;
	int			x;
	int			y;
	int			z;
	int			z1;
	t_mlx		p;
	t_point		*point;
}					t_map;



int		fdf(int fd, char *map);

#endif
