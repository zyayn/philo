/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:18:49 by zchia             #+#    #+#             */
/*   Updated: 2023/09/15 00:28:51 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
	{
		len = 0;
		start = ft_strlen(s);
	}
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, &s[start], len + 1);
	return (substr);
}
/*
int	main(void)
{
	char	str[] = "The quick brown fox jumps over the lazy dog.";
	char	*sub;

	sub = ft_substr(str, 400, 20);
	printf("%s\n", sub);
	return (0);
}
*/
