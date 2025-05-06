/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 12:24:37 by mcecchel          #+#    #+#             */
/*   Updated: 2024/12/03 12:55:58 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*------------------------------------------------------------------------------
La funzione split è progettata per dividere una stringa `s` in un array di
stringhe in base a un carattere delimitatore specificato `c`.
Questa funzione serve per analizzare stringhe in cui gli elementi sono separati
da un carattere specifico.

La funzione restituisce l'array di interi.
------------------------------------------------------------------------------*/
#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	counter;
	size_t	word;

	counter = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && word == 0)
		{
			word = 1;
			counter++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (counter);
}

static char	*copy_words(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	if (start == NULL || len == 0)
		return (NULL);
	word = ft_calloc(sizeof(char), (len + 1));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

static const char	*skip_delimiters(const char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char		**result;
	size_t		counter;
	size_t		i;
	const char	*start;

	if (s == NULL)
		return (NULL);
	counter = count_words(s, c);
	result = (char **)ft_calloc((counter +1), sizeof(char *));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		s = skip_delimiters(s, c);
		if (*s == '\0')
			break ;
		start = s;
		while (*s && *s != c)
			s++;
		result[i] = copy_words(start, s - start);
		i++;
	}
	result[i] = NULL;
	return (result);
}
/* int	main()
{
	char *str = ",,Giallo,,Rosso,,Verde,,Blu,,";
	char	c = ',';
	char	**result = ft_split(str, c);
	size_t	i = 0;

 	if (result == NULL)
	{
		printf("Errore nell'allocazione della memoria\n");
		return (1);
	}
	else
	{
		while (result[i] != NULL)
		{
			printf("Parola: %s\n", result[i]);
			free(result[i]);
			i++;
		}
	}
	free(result);
	return (0);
} */