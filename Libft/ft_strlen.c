/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:24:35 by mcecchel          #+#    #+#             */
/*   Updated: 2024/11/29 15:41:25 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
/*
int	main(void)
{
	char	*a;
	int		b;

	a = "Primo giorno col botto";
	b = ft_strlen(a);
	printf("Lunghezza della stringa '%s' è %d\n", a, b);
	return (0);
}*/