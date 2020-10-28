/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:53:31 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/28 10:19:23 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/fdf.h"

int     main(int argc, char **argv)
{
    int fd;

    if (argc == 2)
    {
    fd = open(argv[1], O_RDONLY);
    fdf(fd, argv);
    }
}
