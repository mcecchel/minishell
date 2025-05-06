/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexamin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:44:31 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/04 15:57:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthexamin(unsigned int nbr)
{
	if (nbr >= 16)
	{
		ft_puthexamin(nbr / 16);
		ft_puthexamin(nbr % 16);
	}
	else
	{
		if (nbr < 10)
			ft_putchar(nbr + '0');
		else
			ft_putchar(nbr + 'a' - 10);
	}
	return (ft_hex_counter(nbr));
}
