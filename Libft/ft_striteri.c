/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:35:05 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:59:10 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**/
/*------------------------------------------------------------------------------
La funzione  applica una funzione definita dall'utente a ogni carattere di
una stringa, utilizzando l'indice di ciascun carattere come parametro aggiuntivo.
La differenza rispetto ad altre funzioni simili è che striteri modifica la
stringa originale in-place senza creare una copia.
------------------------------------------------------------------------------*/
#include "libft.h"

/* static void	ft_toupper(unsigned int i, char *c)
{
	(void)i; // parametro inutilizzato
	if (*c >= 'a' && *c <= 'z')
		*c = *c - 32;
} */
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
	s[i] = '\0';
}
/* int	main()
{
	char	str[] = "Se ni’ mondo esistesse un po’ di bene";

	ft_striteri(str, ft_toupper);
	printf("Stringa modificata: %s\n", str);
	return (0);
} */