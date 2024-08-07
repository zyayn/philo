/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 21:35:05 by zchia             #+#    #+#             */
/*   Updated: 2023/09/10 21:35:31 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
/*
int	main(void)
{
	const char	*src;
	char		*dst;

	src = "Hello";
	dst = "World";
	ft_memmove(dst, src, 5);
	printf("%s", dst);
	return (0);
}
*/
