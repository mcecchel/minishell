/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:17:43 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:17 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione Atoi converte una stringa in un numero intero. Prende un singolo
argomento(nptr), puntatore alla stringa da convertire.

Restituisce il risultato finale (result moltiplicato per il segno) per eventuali
segni negativi.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (result * sign);
}
/* int	main()
{
	char	str1[] = " 42";
	char	str2[] = " -42";
	char	str3[] = "abc42";
	char	str4[] = "42abc";

	printf("Risultato: %d\n", ft_atoi(str1));
	printf("Risultato: %d\n", ft_atoi(str2));
	printf("Risultato: %d\n", ft_atoi(str3));
	printf("Risultato: %d\n", ft_atoi(str4));
	return (0);
} */