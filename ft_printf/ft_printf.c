/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:33:25 by zchia             #+#    #+#             */
/*   Updated: 2023/09/20 18:40:05 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	getformat(va_list args, char conv)
{
	int		count;
	char	*s;

	count = 0;
	if (conv == 'c')
		count = ft_putchar_fd(va_arg(args, int), 1);
	else if (conv == '%')
		count = ft_putchar_fd('%', 1);
	else if (conv == 's')
		s = ft_getstr(va_arg(args, char *));
	else if (conv == 'p')
		s = ft_ptoa(va_arg(args, unsigned long));
	else if (conv == 'd' || conv == 'i')
		s = ft_itoa(va_arg(args, int));
	else if (conv == 'u')
		s = ft_uitoa(va_arg(args, unsigned int));
	else if (conv == 'X' || conv == 'x')
		s = ft_htoa(va_arg(args, unsigned int), conv);
	if (conv != 'c' && conv != '%')
	{
		count = ft_putstr_fd(s, 1);
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
			ft_putchar_fd(*param, 1);
			count++;
		}
		param++;
	}
	va_end(args);
	return (count);
}
/*
int	main(void)
{
//	int	num;
	int	count;

//	num = 77;
//	count = ft_printf("%+40d, %u, %d, %.   .s\n", num, 0, 42, "apple");
	count = ft_printf("ft_printf: %p %p %p\n", 0, 15, 16);
	printf("printf: %p\n", &count);
	printf("count = %d\n", count);
	return (0);
}
*/
