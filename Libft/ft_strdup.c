/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:43:45 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:58:51 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strdup duplica una stringa data. La funzione prende un singolo
argomento `s`, che è un puntatore alla stringa da duplicare.

La funzione restituisce il puntatore `str`, che punta alla stringa duplicata.
------------------------------------------------------------------------------*/
#include "libft.h"
/*len = ft_strlen :Calcolo la lunghezza della stringa di origine
str = malloc :Alloco la memoria
while :Copio la stringa di origine nella stringa appena allocata*/

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*str;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	str = ft_calloc(sizeof(char), (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/* int	main()
{
	char *original = "Buona sta tisanina";
	char *copy = ft_strdup(original);
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