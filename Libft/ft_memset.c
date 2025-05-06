/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:23:42 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:32 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione memset imposta i primi `n` byte dell'area di memoria puntata da `s`
al valore specificato `c`. La funzione prende tre argomenti:
s (puntatore all'area di memoria da riempire); c (il carattere da impostare) e
n (il numero di byte da riempire).

La funzione restituisce il puntatore `s`, che punta all'area di memoria con i
byte riempiti.
------------------------------------------------------------------------------*/
#include "libft.h"
/*s = puntatore ad area memoria,
c = carattere da impostare,
n = numero byte da riempire*/

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			z;

	ptr = (unsigned char *)s;
	c = (unsigned char)c;
	z = 0;
	while (z < n)
	{
		ptr[z] = c;
		z++;
	}
	return (s);
}
/* int main()
{
	char buffer[] = "DCDCDCDCDCDCDCDCDCDC";

	ft_memset(buffer, 'X', 10);
	printf("Buffer: %s\n", buffer);
	return (0);
} */
