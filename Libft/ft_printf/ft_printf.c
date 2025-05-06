/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:50:10 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/04 15:57:56 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_check(char str, va_list args)
{
	int	count;

	if (str == '0')
		return (0);
	count = 0;
	if (str == 'c')
		count = ft_putchar(va_arg(args, int));
	else if (str == 's')
		count = ft_putstr(va_arg(args, char *));
	else if (str == 'd' || str == 'i')
		count = ft_putdecimal(va_arg(args, int));
	else if (str == 'u')
		count = ft_putunsign(va_arg(args, unsigned int));
	else if (str == 'x')
		count = ft_puthexamin(va_arg(args, unsigned int));
	else if (str == 'X')
		count = ft_puthexamai(va_arg(args, unsigned int));
	else if (str == 'p')
		count = ft_putptr((void *)va_arg(args, unsigned long));
	else if (str == '%')
		count = ft_percent();
	return (count);
}

int	ft_printf(const char *str, ...)
{
	const char	*ptr;
	va_list		args;
	int			count;

	va_start(args, str);
	ptr = str;
	count = 0;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			count += ft_printf_check(*ptr, args);
			ptr++;
		}
		else
		{
			count += ft_putchar(*ptr);
			ptr++;
		}
	}
	va_end(args);
	return (count);
}
/* 
int	main(void)
{
	printf("Originale: %c\n", 'M');
	ft_printf("Mia: %c\n", 'M');
	printf("Originale: %s\n", "Ciao mmmmmerde");
	ft_printf("Mia: %s\n", "Ciao mmmmmerde");
	printf("Originale: %d\n", 42);
	ft_printf("Mia: %d\n", 42);
	printf("Originale: %i\n", 24);
	ft_printf("Mia: %i\n", 24);
	printf("Originale: %u\n", 42);
	ft_printf("Mia: %u\n", 42);
	printf("Originale: %x\n", 42);
	ft_printf("Mia: %x\n", 42);
	printf("Originale: %X\n", 42);
	ft_printf("Mia: %X\n", 42);
	printf("Originale: %p\n", "24");
	ft_printf("Mia: %p\n", "24");
	printf("Originale: %%\n");
	ft_printf("Mia: %%\n");
	return (0);
} */
