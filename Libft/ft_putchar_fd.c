/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:03:58 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:55:00 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione putchar_fd sfrutta la chiamata di sistema write per scrivere un
carattere sul file descriptor specificato. Il carattere viene passato come primo
argomento alla funzione. La write è responsabile di inviare il dato al file, al
terminale o a un altro dispositivo legato al file descriptor.
= Scrive un byte (il carattere `c`) sul file descriptor `fd`
------------------------------------------------------------------------------*/
#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/* int	main()
{
	ft_putchar_fd('M', 1);
	return (0);
} */
