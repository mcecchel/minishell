/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:49:49 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:09:14 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strnstr cerca la prima occorrenza della sottostringa `little`
all'interno della stringa `big` fino a `len` caratteri. La funzione restituisce
un puntatore all'inizio della sottostringa individuata, oppure `NULL` se la
sottostringa non viene trovata entro la lunghezza specificata.

La funzione restituisce un puntatore all'inizio della sottostringa individuata
in `big`.Se non viene trovata alcuna corrispondenza, restituisce NULL,
indicando che la sottostringa `little` non è stata trovata entro la lunghezza
(len) specificata.
------------------------------------------------------------------------------*/
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (i < len && big[i] != '\0')
	{
		if (big[i] == little[0])
		{
			j = 1;
			while ((i + j) < len && (little[j] != '\0') \
			&& (big[i + j] == little[j]))
				j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
/* int	main()
{
	const char	*big = "Ciao, come stai?";
	const char	*little = "co";
	char		*result = ft_strnstr(big, little, 50);
	
	if (result)
		printf("Sottostringa trovata: %s\n", result);
	else
		printf("Sottostringa non trovata :(\n");
	return (0);
} */