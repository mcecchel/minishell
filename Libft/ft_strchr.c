/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:55:41 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:08:30 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strchr cerca la prima occorrenza di un carattere specificato `c`
nella stringa `s`. La funzione prende due argomenti: `s`, un puntatore alla
stringa da cercare, e `c`, il carattere da cercare.

Se non viene trovata una corrispondenza e `c` è il terminatore nullo (`'\0'`),
la funzione restituisce un puntatore alla ricorrenza.
Se `c` non viene trovato e non è il terminatore nullo, la funzione restituisce
NULL, indicando che il carattere non è stato trovato nella stringa.
------------------------------------------------------------------------------*/
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
/* int	main()
{
	const char	*s = "Mi do fuoco";
	char	c = '\0';
	char	*search = ft_strchr(s, c);

	if (search != NULL)
		printf("Carattere '%c' in posizione: %ld\n", c, search - s);
	else
		printf("Carattere '%c' non trovato :(\n", c);
	return (0);
}
//(search - s) = distanza tra il ptr *search e l'inizio della stringa
*/
