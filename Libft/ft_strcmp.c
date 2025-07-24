/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:02:11 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/24 13:56:36 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/* int main(void)
{
	printf("Comparison: %d\n", ft_strcmp("ciao", "ciao"));
	printf("Comparison: %d\n", ft_strcmp("ciab", "ciaa"));
	printf("Comparison: %d\n", ft_strcmp("ciab", "ciac"));
	return (0);
} */