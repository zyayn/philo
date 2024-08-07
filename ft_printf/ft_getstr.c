/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:55:37 by zchia             #+#    #+#             */
/*   Updated: 2023/09/24 14:00:01 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
