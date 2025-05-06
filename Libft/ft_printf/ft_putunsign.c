/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:51:12 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/04 15:57:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsign(unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr == UINT_MAX)
	{
		ft_putstr("4294967295");
		return (count + 10);
	}
	if (nbr >= 10)
	{
		count = ft_putunsign(nbr / 10);
		ft_putchar(nbr % 10 + '0');
		count++;
	}
	else
	{
		ft_putchar(nbr + '0');
		count++;
	}
	return (count);
}
