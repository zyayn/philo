/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:04:05 by zchia             #+#    #+#             */
/*   Updated: 2024/07/15 01:04:05 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*whitespace(const char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	checksign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (-1);
	}
	else if (**str == '+')
		(*str)++;
	return (1);
}

int	get_preresult(const char **str)
{
	int	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + **str - '0';
		(*str)++;
	}
	return (result);
}

double	get_postresult(int post_nbr, int decimal_places)
{
	double	divisor;
	int		i;

	divisor = 1.0;
	i = 0;
	while (i < decimal_places)
	{
		divisor *= 10.0;
		i++;
	}
	return (post_nbr / divisor);
}

double	ft_atod(const char *str)
{
	double	result;
	double	post_nbr;
	int		sign;
	int		decimal_places;

	str = whitespace(str);
	sign = checksign(&str);
	post_nbr = 0.0;
	decimal_places = 0;
	result = get_preresult(&str);
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			post_nbr = post_nbr * 10.0 + *str - '0';
			decimal_places++;
			str++;
		}
		result += get_postresult(post_nbr, decimal_places);
	}
	return (sign * result);
}
