/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:18:10 by hsennane          #+#    #+#             */
/*   Updated: 2024/11/23 11:18:15 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	indice_de_debut(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (!set[0])
		return (0);
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (!set[j + 1])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

static int	indice_de_fin(char const *s1, char const *set)
{
	int	i;
	int	j;

	if (!set[0])
		return (ft_strlen(s1) - 1);
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
				break ;
			if (!set[j + 1])
				return (i);
			j++;
		}
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t;
	int		d;
	int		f;
	int		i;

	if (!s1 || !set)
		return (NULL);
	d = indice_de_debut(s1, set);
	f = indice_de_fin(s1, set);
	if (d > f)
		t = malloc(sizeof(char) * 1);
	else
		t = malloc(sizeof(char) * (f - d + 2));
	if (!t)
		return (NULL);
	i = 0;
	while (d <= f)
	{
		t[i] = s1[d];
		i++;
		d++;
	}
	t[i] = '\0';
	return (t);
}
