/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:41:57 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:06:52 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione toupper converte una lettera minuscola nella corrispondente
maiuscola. La funzione accetta un unico argomento: c (intero che rappresenta il
carattere da convertire).

Restituzione del valore:
- Se c è stato convertito, viene restituita la lettera maiuscola.
- Se c non è una lettera minuscola, la funzione restituisce semplicemente il
valore originale, senza modificarlo.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/* int  main()
{
	char lower = 'g';
	char upper = 'G';
	char symbol = '!';

	printf("Carattere originale: %c -> %c\n", lower, ft_tolower(lower));
	printf("Carattere originale: %c -> %c\n", upper, ft_tolower(upper));
	printf("Carattere originale: %c -> %c\n", symbol, ft_tolower(symbol));
	return (0);
} */