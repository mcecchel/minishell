/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:51:12 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:35:50 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunsign(int fd, unsigned int nbr)
{
	int	count;

	count = 0;
	if (nbr == UINT_MAX)
	{
		ft_putstr_pf(fd, "4294967295");
		return (count + 10);
	}
	if (nbr >= 10)
	{
		count = ft_putunsign(fd, nbr / 10);
		ft_putchar_pf(fd, nbr % 10 + '0');
		count++;
	}
	else
	{
		ft_putchar_pf(fd, nbr + '0');
		count++;
	}
	return (count);
}
