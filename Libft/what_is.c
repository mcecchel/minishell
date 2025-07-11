/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:51:45 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/11 17:17:59 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	what_ret(int num, int alpha, int other)
{
	if (alpha == 0 && num == 0 && other == 0)
		return (EMPTY);
	if (alpha == 1 && num == 0 && other == 0)
		return (ALPHA);
	if (alpha == 0 && num == 1 && other == 0)
		return (NUM);
	if (alpha == 1 && num == 1 && other == 0)
		return (ALPHANUM);
	if ((alpha == 1 && num == 1 && other == 1) || (alpha == 0 && num == 1
			&& other == 1) || (alpha == 1 && num == 0 && other == 1))
		return (ALL);
	if (alpha == 0 && num == 0 && other == 1)
		return (OTHERS);
	return (-1);
}

int	what_is(char *str, int n)
{
	int	num;
	int	alpha;
	int	i;
	int	other;
	int	ret;

	num = 0;
	alpha = 0;
	other = 0;
	i = 0;
	ret = 0;
	while (i < n && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = 1;
		else if ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z'))
			alpha = 1;
		else
			other = 1;
		i++;
	}
	ret = what_ret(num, alpha, other);
	return (ret);
}

// const char *desc(int code)
// {
// 			if (code == 0) return "Vuota";
// 			if (code == 1) return "Solo lettere";
// 			if (code == 2) return "Solo numeri";
// 			if (code == 3) return "Lettere e numeri";
// 			if (code == 4) return "Lettere, numeri e altro";
// 			if (code == 5) return "Solo caratteri speciali";
// 			return "Caso non previsto";
// }

// int main(void)
// 	{
// 	char *test[] = {
// 		"",
// 		"abc",
// 		"123",
// 		"abc123",
// 		"abc!",
// 		"123!",
// 		"!@#",
// 		"abc123!",
// 		NULL
// 	};
// 	int i = 0;
// 	while (test[i])
// 	{
// 		int code = what_is(test[i], 100);
// 		printf("Test \"%s\": %s (codice %d)\n", test[i], desc(code), code);
// 		i++;
// 	}
// 	return 0;
// 	}
