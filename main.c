/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 19:53:31 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/20 20:06:42 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int     main(int argc, char **argv)
{
    int i;
    char *line;
    if (argc == 2)
    {
        i = open(argv[1], O_RDONLY);
        read(i, &);
    }
}