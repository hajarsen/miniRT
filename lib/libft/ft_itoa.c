/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsennane <hsennane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:15:26 by hsennane          #+#    #+#             */
/*   Updated: 2024/11/23 14:15:30 by hsennane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(long nbr)
{
	int	length;

	length = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr = nbr / 10;
		length++;
	}
	return (length);
}

static int	ft_sign(long nbr)
{
	if (nbr < 0)
	{
		return (1);
	}
	return (0);
}

static void	nbr_to_str(char *s, long nbr, int length, int sign)
{
	while (length--)
	{
		s[length + sign] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
}

char	*ft_itoa(int n)
{
	int		length;
	char	*s;
	long	nbr;
	int		sign;

	nbr = (long)n;
	sign = ft_sign(nbr);
	length = ft_length(nbr);
	if (sign == 1)
		nbr *= -1;
	s = malloc((sizeof(char)) * (length + sign + 1));
	if (!s)
		return (NULL);
	if (sign == 1)
		s[0] = '-';
	nbr_to_str(s, nbr, length, sign);
	s[length + sign] = '\0';
	return (s);
}
