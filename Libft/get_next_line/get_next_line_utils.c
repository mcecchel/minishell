/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 14:06:52 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/10 10:52:00 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s != NULL && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char)c;
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (src == NULL && dest == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (dest > src && dest < (src + n))
	{
		d += n - 1;
		s += n - 1;
		while (n--)
			*d-- = *s--;
	}
	else
	{
		while (n--)
			*d++ = *s++;
	}
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
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
