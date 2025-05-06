/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:55:52 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:30 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione isascii controlla se un dato carattere è un carattere ASCII. La
funzione accetta un singolo argomento: c(un int che rappresenta il carattere da
controllare).

La funzione restituisce `0 o 1`, indicando se il carattere è ASCII.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
/*
int main(void)
{
    int	x = 77;
    int	y = 130;
    int	c;

    c = ft_isascii(x);
    printf("Ascii: %d\n", c);
    c = ft_isascii(y);
    printf("Non ascii: %d\n", c);
    return (0);
}*/