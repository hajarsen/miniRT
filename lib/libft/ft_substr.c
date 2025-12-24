/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:53:48 by hsennane          #+#    #+#             */
/*   Updated: 2024/11/19 18:09:47 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	new_len;
	char	*sub_str;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		sub_str = malloc(sizeof(char));
		if (!sub_str)
			return (NULL);
		sub_str[0] = '\0';
	}
	else
	{
		new_len = ft_strlen(s + start);
		if (new_len < len)
			len = new_len;
		sub_str = malloc(sizeof(char) * (len + 1));
		if (!sub_str)
			return (NULL);
		ft_strlcpy(sub_str, s + start, len + 1);
	}
	return (sub_str);
}
