/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:29:04 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:03:50 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione strncmp confronta fino a `n` caratteri di due stringhe s1 e s2.
La funzione restituisce un int minore, uguale o maggiore di zero se s1 risulta
rispettivamente minore, uguale o maggiore di `s2`.

Se il ciclo si conclude trovando una differenza tra i caratteri confrontati, la
funzione restituisce la differenza stessa castata in unsigned char per gestire
correttamente eventuali valori negativi.
Se il ciclo si conclude senza trovare differenze, restituisce 0, indicando che
i primi `n` caratteri di s1 e s2 sono uguali.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
/* int	main()
{
	char	str1[] = "Ciao";
	char	str2[] = "Ciano";
	char 	str3[] = "Ciapo";

	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str2, ft_strncmp(str1, str2, 0));
	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str2, ft_strncmp(str1, str2, 5));
	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str3, ft_strncmp(str1, str3, 5));
	return (0);
} */
