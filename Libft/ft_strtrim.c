/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:58:38 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:06:14 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strtrim rimuove i caratteri specificati dall'inizio e dalla fine di
una determinata stringa s1. I caratteri da rimuovere sono specificati nella
stringa set. Restituisce una nuova stringa con i caratteri specificati tagliati
da entrambe le estremità.

Restituisce il puntatore `trimmed`, che punta alla nuova stringa creata.
------------------------------------------------------------------------------*/
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != NULL)
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]) != NULL)
		end--;
	trimmed = malloc(end - start + 1);
	if (trimmed == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		trimmed[i] = s1[start];
		i++;
		start++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
/* int	main()
{
	const char	*str = "   Bagno in piscina con un tostapane   ";
	const char	*set = " ";
	char	*trimmed = ft_strtrim(str, set);
	
	if (trimmed == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	else
	{
		printf("Stringa originale: %s\n", str);
		printf("Stringa trimmata: %s\n", trimmed);
	}
	free(trimmed);
	return (0);
} */
