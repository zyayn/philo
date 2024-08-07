/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:15:37 by zchia             #+#    #+#             */
/*   Updated: 2023/09/08 17:19:05 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	i = 0;
	while (i < n)
	{
		((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	const char	*src;
	char		*dst;

	src = "Hello";
	dst = "\0";
	ft_memcpy(dst, src, 5);
	printf("%s", dst);
	return (0);
}
*/
