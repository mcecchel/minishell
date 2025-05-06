/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:12:07 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:06:43 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione tolower converte una lettera maiuscola nella corrispondente lettera
minuscola. Input: La funzione accetta un argomento c, un intero che rappresenta
il carattere da convertire.

Ritorno del valore:
- Se il carattere è maiuscolo, restituisce il valore convertito.
- Se non è maiuscolo, restituisce il valore di c senza modifiche.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/* int	main()
{
	char lower = 'g';
	char upper = 'G';
	char symbol = '!';

	printf("Carattere originale: %c -> %c\n", lower, ft_tolower(lower));
	printf("Carattere originale: %c -> %c\n", upper, ft_tolower(upper));
	printf("Carattere originale: %c -> %c\n", symbol, ft_tolower(symbol));
	return (0);
} */
