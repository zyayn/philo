/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 01:39:10 by zchia             #+#    #+#             */
/*   Updated: 2024/08/11 22:32:04 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

char	*ft_getstr(char *s)
{
	char	*str;
	int		len;

	if (s)
		len = ft_strlen(s);
	else
		len = 6;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (s)
		ft_strlcpy(str, s, len + 1);
	else
		ft_strlcpy(str, "(null)", len + 1);
	return (str);
}
