/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:05:23 by zchia             #+#    #+#             */
/*   Updated: 2023/09/12 17:06:54 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (!size || size <= dstlen)
		return (srclen + size);
	i = 0;
	j = dstlen;
	while (src[i] && i < (size - dstlen - 1))
		dst[j++] = src[i++];
	dst[j] = '\0';
	if (dstlen > size)
		return (srclen + size);
	else
		return (srclen + dstlen);
	return (i);
}
/*
int	main(void)
{
	
	return (0);
}
*/