/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:47:32 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:06:04 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strrchr cerca l'ultima occorrenza di un carattere specificato `c`
nella stringa `s`.La funzione restituisce un puntatore all'ultima occorrenza
del carattere, oppure `NULL` se il carattere non viene trovato.

La funzione restituisce un puntatore al primo carattere della stringa s[i] = c.
In caso contrario, restituisce NULL (= il carattere non è stato trovato).
------------------------------------------------------------------------------*/
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}
/* int	main()
{
	const char	*s = "\0\0";
	char	c = '\0';
	char	*search = ft_strrchr(s, c);

	if (search != NULL)
		printf("Carattere '%c' in posizione: %ld\n", c, search - s);
	//search - s = distanza tra ptr search l'inizio della stringa
	else
		printf("Carattere '%c' non trovato :(\n", c);
	return (0);
} */