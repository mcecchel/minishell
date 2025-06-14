/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:25 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:32:02 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_puthex(int fd, uintptr_t nbr)
{
	const char	*hex_digit;
	char		buff_hex[16];
	int			i;
	int			count;

	hex_digit = "0123456789abcdef";
	if (nbr == 0)
	{
		write(fd, "0", 1);
		return (1);
	}
	i = 0;
	while (nbr > 0)
	{
		buff_hex[i++] = hex_digit[nbr % 16];
		nbr = nbr / 16;
	}
	count = 0;
	while (i > 0)
	{
		write(fd, &buff_hex[--i], 1);
		count++;
	}
	return (count);
}

int	ft_putptr(int fd, void *ptr)
{
	uintptr_t	address;
	int			count;

	if (ptr == NULL)
	{
		write(fd, "(nil)", 5);
		return (5);
	}
	address = (uintptr_t)ptr;
	count = write(fd, "0x", 2);
	count = count + ft_puthex(fd, address);
	return (count);
}
