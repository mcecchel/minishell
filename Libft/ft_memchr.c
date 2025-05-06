/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:59:27 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:07 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione memchr cerca la prima occorrenza di un byte specificato in un blocco
di memoria. La funzione accetta tre argomenti: un puntatore `s` al blocco di
memoria da cercare, un int `c`(che rappresenta il byte da cercare) e una
variabile size_t `n`(numero byte del blocco di memoria puntato da 's' che
specifica quindi il numero di byte da cercare).

Se viene trovata una corrispondenza, la funzione restituisce ptr (che punta alla
posizione del byte corrispondente), Se non viene trovata alcuna corrispondenza,
alla fine del ciclo la funzione restituisce NULL.
------------------------------------------------------------------------------*/
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	while (n--)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	return (NULL);
}
/* int	main()
{
	const char	*s = "Mi do fuoco";
	char	c = 'a';
	size_t n = 10;
	char	*search = ft_memchr(s, c, n);
	
	if (search != NULL)
		printf("Carattere '%c' in posizione: %ld\n", c, search - s);
	else
		printf("Carattere '%c' non trovato :(\n", c);
	return (0);
}  */