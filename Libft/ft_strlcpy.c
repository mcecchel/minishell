/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:11:33 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:00:18 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strlcpy copia una stringa da src a dst, assicurandosi che la stringa
di destinazione sia null-terminated e non superi la dimensione specificata.

La funzione restituisce la lunghezza totale della stringa che ha cercato di
creare (: la lunghezza di src).
------------------------------------------------------------------------------*/
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	srclen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (size == 0)
		return (srclen);
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}
/* int	main(void)
{
	char	src[] = "Accidenti ad andare a letto tardi";
	char	dst[5] = "";
	size_t	copy;
	
	copy = ft_strlcpy(dst, src, 34);
	printf("Sorgente: %s\n", src);
    printf("Destinazione: %s\n", dst);
    printf("Lunghezza sorgente: %zu\n", copy);
	return (0);
} */