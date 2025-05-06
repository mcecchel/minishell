/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:11:00 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:15 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione memmove copia `n` byte dal blocco di memoria di origine src al
blocco di memoria di destinazione dest. La funzione è progettata per gestire in
modo sicuro le regioni di memoria che si sovrappongono (a differenza di memcpy).

La funzione restituisce il puntatore `dest`, che punta al blocco di memoria di
destinazione con i byte copiati.
------------------------------------------------------------------------------*/
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (dest > src && dest < (src + n))
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}
/* int	main ()
{
	char src[] = "abcdefgh";
	char dest[10];
	ft_memmove(dest, src, 8);
	printf("Dest senza sovrapposizione: %s\n", dest);

	char src[] = "abcdefgh";
	ft_memmove(src + 2, src, 6);
	printf("Src (sovrapposizione dest > src): %s\n", src);

	char src[] = "abcdefgh";
	ft_memmove(src, src + 2, 6);
	printf("Src (overlap dest < src): %s\n", src);
	return (0);
} */