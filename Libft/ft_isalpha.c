/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:21:49 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:52:28 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione isalpha controlla se un dato carattere è una lettera. La funzione
accetta un singolo argomento: c(un int che rappresenta il carattere da
controllare).

La funzione restituisce `0 o 1`, indicando se il carattere è alfabetico.
------------------------------------------------------------------------------*/
#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c < 'A' || c > 'Z') && (c < 'a' || c > 'z'))
		return (0);
	else
		return (1);
}
/*
int main(void)
{
    int	x = 'A';
    int	y = '1';
    int	z = '\n';
    int	c;

    c = ft_isalpha(x);
    printf("Lettera: %d\n", c);
    c = ft_isalpha(y);
    printf("Diverso da lettera: %d\n", c);
    c = ft_isalpha(z);
	printf("Con str vuota: %d\n", c);
    return (0);
}*/