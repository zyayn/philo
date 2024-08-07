/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:38:45 by zchia             #+#    #+#             */
/*   Updated: 2023/09/22 17:39:02 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	lengthofint(unsigned int n)
{
	int	len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_uitoa(unsigned int n)
{
	char			*str;
	int				len;

	len = lengthofint(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (n != 0)
	{
		str[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}
