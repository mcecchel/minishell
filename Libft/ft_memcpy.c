/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:03:23 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:13 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione memcpy copia `n` byte dal blocco di memoria di origine `src` al
blocco di memoria di destinazione `dest`. La funzione prende tre argomenti:
dest (puntatore al blocco di memoria di destinazione), src(puntatore al blocco
di memoria di origine), e n(il numero di byte da copiare).

La funzione restituisce il puntatore `dest`, che punta al blocco di memoria
di destinazione con i byte copiati.
------------------------------------------------------------------------------*/
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
/* int	main ()
{
	char src[] = "Sono stanca capo";
	char dest[] = "Uffi, voglio andare a casa";
	size_t n = 4;

    printf("Sorgente: %s\n", src);
	printf("Destinazione: %s\n", dest);
	ft_memcpy(dest, src, n);
	printf("Risultato: %s\n", dest);
	return (0);
} */