/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eprusako <eprusako@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 11:13:58 by eprusako          #+#    #+#             */
/*   Updated: 2020/10/16 12:37:23 by eprusako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinfree(char const *s1, char const *s2, int left, int right)
{
	char	*new;

	if (!s1 || !s2)
		return (0);
	new = ft_strnew(ft_strlen((char *)s1) + ft_strlen((char *)s2));
	if (!new)
		return (0);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	if (left == 1)
		free((void *)s1);
	if (right == 1)
		free((void *)s2);
	return (new);
}
