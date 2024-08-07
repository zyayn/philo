/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:22:28 by zchia             #+#    #+#             */
/*   Updated: 2023/09/14 20:32:07 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*alloc;
	int		i;
	int		size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	alloc = (char *)malloc(sizeof(char) * (size + 1));
	if (!alloc)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		alloc[i] = s1[i];
		i++;
	}
	alloc[i] = '\0';
	return (alloc);
}
