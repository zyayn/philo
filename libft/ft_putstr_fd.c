/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:39:10 by zchia             #+#    #+#             */
/*   Updated: 2024/07/15 23:03:40 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	size;

	size = ft_strlen(s);
	i = 0;
	while (i < size)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (size);
}
