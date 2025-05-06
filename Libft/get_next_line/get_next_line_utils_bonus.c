/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:54:53 by mcecchel          #+#    #+#             */
/*   Updated: 2025/02/04 18:47:28 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc(s1len + s2len + 1 * sizeof(char));
	if (newstr == NULL)
		return (free(s1), NULL);
	i = 0;
	while (s1 != NULL && i < s1len)
	{
		newstr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		newstr[s1len + i] = s2[i];
		i++;
	}
	newstr[s1len + s2len] = '\0';
	return (newstr);
}
