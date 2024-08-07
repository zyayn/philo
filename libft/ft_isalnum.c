/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:40:31 by zchia             #+#    #+#             */
/*   Updated: 2023/09/07 15:41:35 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	if (ft_isalnum('!'))
		write(1, "It's an alphanumeric!", 21);
	else
		write(1, "Not an alphanumeric..", 21);
	return (0);
}
*/
