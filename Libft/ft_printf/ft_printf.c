/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:50:10 by mcecchel          #+#    #+#             */
/*   Updated: 2025/06/17 15:29:56 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_check(int fd, char str, va_list *args)
{
	int	count;

	if (str == '0')
		return (0);
	count = 0;
	if (str == 'c')
		count = ft_putchar_pf(fd, va_arg(*args, int));
	else if (str == 's')
		count = ft_putstr_pf(fd, va_arg(*args, char *));
	else if (str == 'd' || str == 'i')
		count = ft_putdecimal_fd(fd, va_arg(*args, int));
	else if (str == 'u')
		count = ft_putunsign(fd, va_arg(*args, unsigned int));
	else if (str == 'x')
		count = ft_puthexamin(fd, va_arg(*args, unsigned int));
	else if (str == 'X')
		count = ft_puthexamai(fd, va_arg(*args, unsigned int));
	else if (str == 'p')
		count = ft_putptr(fd, (void *)va_arg(*args, unsigned long));
	else if (str == '%')
		count = ft_percent_fd(fd);
	return (count);
}

int	printf_body(int fd, const char *ptr, va_list *args)
{
	int			count;

	count = 0;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			count += ft_printf_check(fd, *ptr, args);
			ptr++;
		}
		else
		{
			count += ft_putchar_pf(fd, *ptr);
			ptr++;
		}
	}
	return (count);
}

int	printf_debug(const char *str, ...)
{
	va_list		args;
	int			count;

	if (!DEBUG)
		return (-1);
	va_start(args, str);
	count = printf_body(2, str, &args);
	va_end(args);
	return (count);
}

int	fd_printf(int fd, const char *str, ...)
{
	va_list		args;
	int			count;

	va_start(args, str);
	count = printf_body(fd, str, &args);
	va_end(args);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;

	va_start(args, str);
	count = printf_body(1, str, &args);
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
