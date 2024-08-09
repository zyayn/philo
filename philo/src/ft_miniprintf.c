/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_miniprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:33:25 by zchia             #+#    #+#             */
/*   Updated: 2024/08/09 19:58:03 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr(char *s)
{
	int	i;
	int	size;

	size = ft_strlen(s);
	i = 0;
	while (i < size)
	{
		write(1, &s[i], 1);
		i++;
	}
	return (size);
}

static int	lengthofint(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		len;

	nbr = n;
	len = lengthofint(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	len--;
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

static int	getformat(va_list args, char conv)
{
	int		count;
	char	*s;

	count = 0;
	if (conv == '%')
	{
		write(1, "%", 1);
		count = 1;
	}
	else if (conv == 's')
		s = ft_getstr(va_arg(args, char *));
	else if (conv == 'd' || conv == 'i')
		s = ft_itoa(va_arg(args, int));
	if (conv != 'c' && conv != '%')
	{
		count = ft_putstr(s);
		free (s);
	}
	return (count);
}

int	ft_printf(const char *param, ...)
{
	int		count;
	va_list	args;

	va_start(args, param);
	count = 0;
	while (*param)
	{
		if (*param == '%')
		{
			count += getformat(args, param[1]);
			param++;
		}
		else
		{
			write(1, &(*param), 1);
			count++;
		}
		param++;
	}
	va_end(args);
	return (count);
}
