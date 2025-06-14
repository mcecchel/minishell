/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexamai.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:44:53 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:51:42 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexamai(int fd, unsigned int nbr)
{
	if (nbr >= 16)
	{
		ft_puthexamai(fd, nbr / 16);
		ft_puthexamai(fd, nbr % 16);
	}
	else
	{
		if (nbr < 10)
			ft_putchar_pf(fd, nbr + '0');
		else
			ft_putchar_fd(fd, nbr + 'A' - 10);
	}
	return (ft_hex_counter(nbr));
}
