/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grmartir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:42:28 by grmartir          #+#    #+#             */
/*   Updated: 2023/02/01 16:29:42 by grmartir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*l;

	l = (0);
	c %= 256;
	while (*s)
	{
		if (*s == c)
			l = (char *)s;
		++s;
	}
	if (l)
		return (l);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
