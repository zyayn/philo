/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:43:19 by zchia             #+#    #+#             */
/*   Updated: 2023/09/24 10:43:39 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	lengthofhex(unsigned long n)
{
	int	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static char	*allocstr(unsigned long nbr, int len)
{
	char	*str;

	if (!nbr)
		str = (char *)malloc(sizeof(char) * (len + 6));
	else
		str = (char *)malloc(sizeof(char) * (len + 3));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_ptoa(unsigned long nbr)
{
	char	*str;
	char	*hex;
	int		len;

	len = lengthofhex(nbr);
	str = allocstr(nbr, len);
	hex = SMALLHEX;
	if (nbr == 0)
		ft_strlcpy(str, "(nil)\0", 6);
	else
	{
		str[0] = '0';
		str[1] = 'x';
		str[len + 2] = '\0';
		len++;
		while (nbr)
		{
			str[len] = hex[(nbr % 16)];
			nbr = nbr / 16;
			len--;
		}
	}
	return (str);
}
