/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:48:35 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:35 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione itoa converte un intero in una stringa null-terminated. La funzione
accetta un singolo argomento n (il numero intero da convertire).

La funzione restituisce la rappresentazione in stringa del numero intero.
------------------------------------------------------------------------------*/
#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	int		sign;

	len = ft_intlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	sign = 1;
	if (n < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	while (len--)
	{
		str[len] = (n % 10) * sign + '0';
		n = n / 10;
		if (len == 0 && sign == -1)
			str[len] = '-';
	}
	return (str);
}
/* int	main()
{
	int	n = -42;
	char	*str;

	str = ft_itoa(n);
	printf("Numero: %d\n", n);
	printf("Stringa: %s\n", str);
	free(str);
	return (0);
} */