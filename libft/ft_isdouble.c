/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:08:31 by zchia             #+#    #+#             */
/*   Updated: 2024/07/15 21:08:31 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	ft_isdouble(const char *str)
{
	int	pre_nbr;
	int	post_nbr;

	pre_nbr = 0;
	post_nbr = 0;
	str = whitespace(str);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		pre_nbr = 1;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			post_nbr = 1;
			str++;
		}
	}
	str = whitespace(str);
	return ((pre_nbr || post_nbr) && *str == '\0');
}
