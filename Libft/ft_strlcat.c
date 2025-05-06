/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:12:50 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:00:05 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strlcat concatena due stringhe. La funzione aggiunge la stringa a
terminazione nulla `src` alla fine della stringa a terminazione nulla `dst`,
assicurandosi che la lunghezza totale della stringa risultante non superi size
byte, incluso il terminatore nullo.

La funzione restituisce la lunghezza totale della stringa che ha cercato di
creare, che è la lunghezza iniziale di `dst` + la lunghezza di `src`.
------------------------------------------------------------------------------*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	dstlen = 0;
	while (dstlen < size && dst[dstlen] != '\0')
		dstlen++;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (size <= dstlen)
		return (size + srclen);
	i = 0;
	while (src[i] != '\0' && (dstlen + i < (size - 1)))
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	if (dstlen + i < size)
		dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
/* int	main(void)
{
	char			dst[50] = "Mi sparo ";
	char			src[] = "una bolla d'aria in vena";
	unsigned int	size = 34;
	unsigned int	combo;

	combo = ft_strlcat(dst, src, size);

	printf("Dst dopo concatenazione: '%s'\n", dst);
	printf("Lunghezza totale: %u\n", combo);
	return (0);
} */