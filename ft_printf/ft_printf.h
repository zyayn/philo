/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchia <zchia@42.sg>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:48:03 by zchia             #+#    #+#             */
/*   Updated: 2024/07/14 16:50:05 by zchia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define CONVERSION "cspdiuxX%"
# define BIGHEX "0123456789ABCDEF"
# define SMALLHEX "0123456789abcdef"

# include <stdarg.h>
# include "../libft/libft.h"

int		ft_printf(const char *param, ...);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_getstr(char *s);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_htoa(unsigned int hnbr, char c);
char	*ft_ptoa(unsigned long nbr);

#endif
