/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexamin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:44:31 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:35:50 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexamin(int fd, unsigned int nbr)
{
	if (nbr >= 16)
	{
		ft_puthexamin(fd, nbr / 16);
		ft_puthexamin(fd, nbr % 16);
	}
	else
	{
		if (nbr < 10)
			ft_putchar_pf(fd, nbr + '0');
		else
			ft_putchar_pf(fd, nbr + 'a' - 10);
	}
	return (ft_hex_counter(nbr));
}
