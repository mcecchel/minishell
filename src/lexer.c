/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/12 15:56:01 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Da fare:
// -Leggere la riga scritta dall’utente (readline())
// -Spezzare il comando in token strutturati
// -Costruire una lista di t_cmd (una per ogni comando tra pipe)
// -Gestire quote, pipe, redirezioni, variabili d’ambiente

#include "minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

// Estrae una parola fino a uno spazio / operatore
char *extract_word(char *line, int *index)
{
	char *word;
	int start;
	int end;

	start = *index;
	end = start;
	while (line[end] && !is_space(line[end]))
		end++;
	if (line[end] == '|' || line[end] == '>' || line[end] == '<')
	{
		end++;
		while (line[end] && is_space(line[end]))
			end++;
	}
	word = ft_substr(line, start, end - start);
	if (!word)
	{
		*index = end;
		return (NULL);
	}
	*index = end;
	return (word);
}

// int main(void)
// {
//     char *line = "echo hello | grep world >> output.txt";
//     int index = 0;
//     char *word = 0;

//     printf("Input line: %s\n", line);
//     printf("Extracted words:\n");

//     while (line[index])
//     {
//         // Salta gli spazi
//         while (line[index] && is_space(line[index]))
//             index++;
//         if (line[index] == '\0')
//             break;

//         word = extract_word(line, &index);
//         if (word)
//         {
//             printf("- %s\n", word);
// 			sleep(1);
//             free(word); // Libera la memoria allocata da ft_substr
//         }
//     }
//     return 0;
// }

// Estrae il contenuto tra virgolette singole o doppie
char *extract_quoted(char *line, int *i)
{

}
