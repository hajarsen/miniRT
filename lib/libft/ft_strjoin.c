/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:50:00 by hsennane          #+#    #+#             */
/*   Updated: 2024/11/23 22:20:04 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*p;
	size_t	index[2];

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!p)
		return (NULL);
	index[0] = 0;
	index[1] = 0;
	while (index[0] < s1_len)
	{
		p[index[0]] = s1[index[0]];
		index[0]++;
	}
	while (index[1] < s2_len)
		p[index[0]++] = s2[index[1]++];
	p[index[0]] = '\0';
	return (p);
}
