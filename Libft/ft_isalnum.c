/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:31:58 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:26 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione isalnume controlla se un dato carattere è alfanumerico. La funzione
accetta un singolo argomento: c(un int che rappresenta il carattere da
controllare).

La funzione restituisce `0 o 1`, indicando se il carattere è alfanumerico.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}
/*
int main(void)
{
    int	x = '7';
    int	y = 'M';
    int	z = '!';
    int	c;

    c = ft_isalnum(x);
    printf("Numero: %d\n", c);
    c = ft_isalnum(y);
    printf("Lettera: %d\n", c);
    c = ft_isalnum(z);
	printf("Diverso da alnum: %d\n", c);
    return (0);
}*/