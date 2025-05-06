/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:54:58 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:06:36 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione substr crea una sottostringa da una stringa data `s`, a partire da
una posizione specificata `start` e con una lunghezza specificata `len`.
La funzione restituisce un puntatore alla nuova sottostringa allocata, oppure
NULL se l'allocazione fallisce o se la stringa di input `s` è NULL.

La funzione restituisce il puntatore `subs`, che punta alla nuova sottostringa
creata.
------------------------------------------------------------------------------*/
#include "libft.h"
/*Parametri: stringa originale, indice di partenza da dove iniziare a
estrarre i caratteri, lunghezza che indica quanti caratteri estrarre*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	subslen;
	char	*subs;
	size_t	i;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		subslen = slen - start;
	else
		subslen = len;
	subs = malloc(subslen + 1);
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < subslen)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
/* int	main()
{
	char	*original = "Buona sta tisanina";
	char	*copy = ft_substr(original, 10, 8);
	if (copy == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	else
	{
		printf("Stringa originale: %s\n", original);
		printf("Stringa copiata: %s\n", copy);
	}
	free(copy);
	return (0);
} */
