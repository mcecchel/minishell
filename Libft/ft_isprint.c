/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:13:11 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:46:40 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione isprint controlla se un dato carattere è un carattere stampabile.
La funzione accetta un singolo argomento `c`, che è un intero che rappresenta il
carattere da controllare.

La funzione restituisce `1`, indicando che il carattere è stampabile. Se è al di
fuori dell'intervallo, restituisce `0` = il carattere non è stampabile.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	else
		return (0);
}
/*
int main(void)
{
    int	x = 77;
    int	y = 4;
    int	c;

    c = ft_isprint(x);
    printf("Printable: %d\n", c);
    c = ft_isprint(y);
    printf("Non printable: %d\n", c);
    return (0);
}*/