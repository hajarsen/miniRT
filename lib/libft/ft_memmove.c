/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 22:17:15 by hsennane          #+#    #+#             */
/*   Updated: 2024/11/23 22:17:16 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	char	*end_dest;
	char	*end_src;

	d = (char *)dst;
	s = (char *)src;
	end_dest = d + len - 1;
	end_src = s + len - 1;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		while (len--)
			*end_dest-- = *end_src--;
	}
	return (dst);
}
