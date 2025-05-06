/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:47:52 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:43:37 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione bzero azzera un blocco di memoria. La funzione prende due argomenti:
un puntatore `s` al blocco di memoria che deve essere azzerato e una variabile
`size_t` `n` che specifica il numero di byte da azzerare.
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			z;

	ptr = (unsigned char *)s;
	z = 0;
	while (z < n)
	{
		ptr[z] = '\0';
		z++;
	}
}
/* int	main()
{
	char buffer[20] = "DCDCDCDCDCDCDCDCDCDC";
	size_t a		= 10;//n di byte da azzerare
	int	b			= 0;

	ft_bzero(buffer, a);
	while (b < 20)
	{
		write(1, &buffer[b], 1);
		b++;
	}
	write(1, "\n", 1);
	return (0);
} */
