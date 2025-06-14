/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdecimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:54:23 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:57:06 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdecimal_fd(int fd, int nbr)
{
	if (nbr == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return (ft_counter(nbr));
	}
	if (nbr < 0)
	{
		ft_putchar_pf(fd, '-');
		nbr = -nbr;
		return (1 + ft_putdecimal_fd(fd, nbr));
	}
	if (nbr == INT_MAX)
	{
		write(fd, "2147483647", 10);
		return (ft_counter(nbr));
	}
	if (nbr >= 10)
	{
		ft_putdecimal_fd(fd, nbr / 10);
		ft_putdecimal_fd(fd, nbr % 10);
	}
	else
		ft_putchar_pf(fd, nbr + '0');
	return (ft_counter(nbr));
}
