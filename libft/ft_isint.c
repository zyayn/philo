/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:42:41 by zchia             #+#    #+#             */
/*   Updated: 2024/08/05 09:42:41 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	ft_isint(const char *str)
{
	int	nbr;

	nbr = 0;
	str = whitespace(str);
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		nbr = 1;
		str++;
	}
	str = whitespace(str);
	return (nbr && *str == '\0');
}
