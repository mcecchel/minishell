/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdecimal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:54:23 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/04 15:57:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putdecimal(int nbr)
{
	if (nbr == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (ft_counter(nbr));
	}
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
		return (1 + ft_putdecimal(nbr));
	}
	if (nbr == INT_MAX)
	{
		write(1, "2147483647", 10);
		return (ft_counter(nbr));
	}
	if (nbr >= 10)
	{
		ft_putdecimal(nbr / 10);
		ft_putdecimal(nbr % 10);
	}
	else
		ft_putchar(nbr + '0');
	return (ft_counter(nbr));
}
