/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 09:08:38 by zchia             #+#    #+#             */
/*   Updated: 2023/09/15 09:54:01 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	char	*front;
	char	*back;
	int		s1size;
	int		strsize;

	if (!s1 || !set)
		return (NULL);
	s1size = ft_strlen(s1);
	front = (char *)s1;
	back = (char *)s1 + s1size - 1;
	while (*front && ft_strchr(set, *front))
		front++;
	while (back > front && ft_strchr(set, *back))
		back--;
	strsize = back - front + 1;
	str = (char *)malloc(sizeof(char) * (strsize + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, front, strsize + 1);
	return (str);
}
/*
int	main(void)
{
	char	str[] = "The quick brown fox jumps over the lazy dog";

	printf("%s", ft_strtrim(str, "og"));
	return (0);
}
*/