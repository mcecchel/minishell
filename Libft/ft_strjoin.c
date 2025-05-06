/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:28 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:59:29 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strjoin è progettata per concatenare due stringhe, s1 e s2, in una
nuova stringa. La funzione prende due argomenti: s1 (puntatore alla prima 
stringa), e s2, un puntatore alla seconda stringa.

L funzione restituisce il puntatore `newstr` che punta alla stringa concatenata.
------------------------------------------------------------------------------*/
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc(s1len + s2len + 1);
	if (newstr == NULL)
		return (NULL);
	i = 0;
	while (i < s1len)
	{
		newstr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		newstr[s1len + i] = s2[i];
		i++;
	}
	newstr[s1len + s2len] = '\0';
	return (newstr);
}
/* int	main()
{
	const char	*str1 = "Ciao ";
	const char	*str2 = "popolo della 42";
	char		*newstr = ft_strjoin(str1, str2);

	if (newstr == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	else
	printf("Stringa concatenata: %s\n", newstr);
	free(newstr);
	return (0);
} */