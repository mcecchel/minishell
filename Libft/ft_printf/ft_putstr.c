/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:21:01 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/14 16:32:04 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_pf(int fd, char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (ft_putstr_pf(fd, "(null)"));
	while (*str)
	{
		ft_putchar_pf(fd, *str);
		str++;
		count++;
	}
	return (count);
}
