/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:22:00 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:32 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione isdigit controlla se un dato carattere è alfanumerico. La funzione
accetta un singolo argomento: c(un int che rappresenta il carattere da
controllare).

La funzione restituisce `1 o 0` se il carattere è numerico.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
/*
int main(void)
{
    int	x = '7';
    int	y = 'M';
    int	z = '\n';
    int	c;

    c = ft_isdigit(x);
    printf("Numero: %d\n", c);
    c = ft_isdigit(y);
    printf("Diverso da numero: %d\n", c);
    c = ft_isdigit(z);
	printf("Con str vuota: %d\n", c);
    return (0);
}*/