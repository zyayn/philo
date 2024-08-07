/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 18:53:31 by zchia             #+#    #+#             */
/*   Updated: 2023/09/22 18:55:51 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	lengthofhex(unsigned int n)
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

char	*ft_htoa(unsigned int nbr, char c)
{
	char	*str;
	char	*hex;
	int		len;

	len = lengthofhex(nbr);
	if (c == 'X')
		hex = BIGHEX;
	else
		hex = SMALLHEX;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (nbr)
	{
		str[len] = hex[(nbr % 16)];
		nbr = nbr / 16;
		len--;
	}
	return (str);
}
