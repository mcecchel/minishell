/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:00:38 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:53:10 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione memcmp confronta due blocchi di memoria. La funzione prende tre
argomenti: s1 e s2 (due puntatori ai blocchi di memoria da confrontare),
e n (numero di byte da confrontare).

Se i byte non sono uguali, la funzione restituisce la differenza tra i due byte.
Se il ciclo si conclude senza trovare alcuna differenza, la funzione restituisce
0, indicando che i due blocchi di memoria sono uguali per i primi `n` byte.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/* int main()
{
	char	str1[] = "Cono";
	char	str2[] = "Bono";
	char 	str3[] = "Dono";
	char	str4[] = "Conosco";

	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str2, ft_memcmp(str1, str2, 1));
	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str3, ft_memcmp(str1, str3, 1));
	printf("Prova tra: '%s' e '%s': %d\n",
	 str1, str4, ft_memcmp(str1, str4, 4));	 
	return (0);
} */
