/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:23:14 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:23 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione Calloc alloca la memoria per un array di elementi e inizializza a
zero tutti i byte della memoria allocata. La funzione accetta due argomenti:
nmemb (numero di elementi da allocare) e size (dimensione di ogni elemento).

La funzione restituisce il puntatore ptr, che punta al blocco di memoria
allocato e inizializzato a zero.
------------------------------------------------------------------------------*/
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	sizetot;
	void	*ptr;

	sizetot = nmemb * size;
	ptr = malloc(sizetot);
	if (ptr != NULL)
		ft_memset(ptr, 0, sizetot);
	return (ptr);
}
/* int main()
{
	int	n = 4;
	int	*array;

	array = (int *)ft_calloc(n, sizeof(int));
	if (array == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	array[0] = 42;
	array[1] = 24;
	array[2] = 73;
	printf("Allocato in arr[0] = %d\n", array[0]);
    printf("Allocato in arr[1] = %d\n", array[1]);
    printf("Allocato in arr[2] = %d\n", array[2]);
	free(array);
	return (0);
} */