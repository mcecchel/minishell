/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:47:53 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 13:00:42 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione `strmapi applica una  funzione (f) a ogni carattere di una stringa
`s`, generando una nuova stringa modificata. La funzione prende due argomenti:
s(puntatore alla stringa di input), e f(puntatore a una funzione che prende
come argomenti un intero senza segno e un carattere e restituisce un carattere).

La funzione restituisce il puntatore `new_str`, che punta alla stringa
modificata appena creata.
------------------------------------------------------------------------------*/
#include "libft.h"

/* static char	ft_toupper(unsigned int i, char c)
{
    (void)i; // parametro inutilizzato
    if (c >= 'a' && c <= 'z')
        return (c - 32);
    return (c);
} */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*new_str;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = f(i, s[i]);
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
/* int	main()
{
	char	*str = "Mi sparo in culo";
	char 	*new_str = ft_strmapi(str, ft_toupper);

	printf("Stringa originale: %s\n", str);
	printf("Stringa modificata: %s\n", new_str);
	free(new_str);
	return (0);	
} */
