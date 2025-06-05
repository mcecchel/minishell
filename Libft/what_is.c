/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:45 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/05 15:56:58 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	what_ret(int num, int alpha, int other)
{
	if (alpha == 0 && num == 0 && other == 0)
		return (0);
	if (alpha == 1 && num == 0 && other == 0)
		return (1);
	if (alpha == 0 && num == 1 && other == 0)
		return (2);
	if (alpha == 1 && num == 1 && other == 0)
		return (3);
	if (alpha == 1 && num == 1 && other == 1)
		return (4);
	if (alpha == 0 && num == 0 && other == 1)
		return (5);
	return (-1);
}

int	what_is(char *str, int n)
{
	int	num;
	int	alpha;
	int	i;
	int	other;
	int	ret;

	num = 0;
	alpha = 0;
	other = 0;
	i = 0;
	ret = 0;
	while (i < n && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = 1;
		else if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
			alpha = 1;
		else
			other = 1;
		i++;
	}
	ret = what_ret(num, alpha, other);
	return (ret);
}
