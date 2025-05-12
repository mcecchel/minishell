/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/12 18:23:02 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    // Increment `end` until a space or operator is encountered
    while (line[end] && !is_space(line[end]) &&
           line[end] != '|' && line[end] != '>' && line[end] != '<' &&
           line[end] != '\'' && line[end] != '\"')
    {
        end++;
    }

    // Skip operators if encountered
    while (line[end] == '|' || line[end] == '>' || line[end] == '<' ||
           line[end] == '\'' || line[end] == '\"')
    {
        end++;
    }

    // Extract the word using ft_substr
    word = ft_substr(line, start, end - start);
    if (!word)
    {
        *index = end;
        return (NULL);
    }

    *index = end; // Update the index to the position after the word
    return (word);
}

// Estrae il contenuto tra virgolette singole o doppie
char *extract_quote(char *line, int *index)
{
	char	quote;
	int		start_quote;
	char	*str;

	str = NULL;
	quote = line[*index];
	(*index)++;// Salto  le quote iniziali
	start_quote = *index;
	while (line[*index] && line[*index] != quote)
		(*index)++;
	if (line[*index] == quote)
	{
		str = ft_substr(line, start_quote, (*index) - start_quote);
		(*index)++;// Salto  le quote finali
	}
	else
		ft_printf("Error: Missing closing quote\n");
		// mettere exit
	return (str);
}

// int main(void)
// {
// 	char *read_line;
// 	int index = 0;
// 	// char *line = "echo 'hello world' | grep \"hello\" > output.txt";
// 	char *quoted;
//     read_line = readline("Prompt > ");
//     printf("%s\n", read_line);

//     printf("Input line: %s\n", read_line);
//     printf("Extracted quoted strings:\n");
//     while (read_line[index])
//     {
// 		printf("daje 1");
// 		while (read_line[index] && is_space(read_line[index]))
//             index++;
//         if (read_line[index] == '\0')
//             break;
// 		printf("daje 2");
//         if (read_line[index] == '\'' || read_line[index] == '\"')
//         {
//             quoted = extract_quote(read_line, &index);
// 			printf("daje 3");
//             if (quoted)
//             {
//                 printf("- %s\n", quoted);
//                 free(quoted); // Libera la memoria allocata da ft_substr
//             }
//         }
//         else
//         {
//             while (read_line[index] && read_line[index] != '\'' && read_line[index] != '\"')
//                 index++;
//         }
//     }
//     return (0);
// }

char *extract_operator(char *line, int *index)
{
    int start = *index;

    // Gestisce operatori singoli o doppi (<<, >>)
    if ((line[*index] == '<' && line[*index + 1] == '<') ||
        (line[*index] == '>' && line[*index + 1] == '>'))
    {
        *index += 2; // Salta gli operatori doppi
    }
    else if (line[*index] == '|' || line[*index] == '<' || line[*index] == '>')
    {
        (*index)++; // Salta l'operatore singolo
    }
    else
    {
        return (NULL); // Non è un operatore
    }

    // Estrae l'operatore
    return ft_substr(line, start, *index - start);
}

int main()
{
	char *read_line;
	int index = 0;
	char *word;
	char *operator;
	char *quoted;

	read_line = readline("Prompt > ");
	printf("%s\n", read_line);

	printf("Input line: %s\n", read_line);
	printf("Extracted tokens:\n");
	while (read_line[index])
	{
		while (read_line[index] && is_space(read_line[index]))
			index++;
		if (read_line[index] == '\0')
			break;
		if (read_line[index] == '\'' || read_line[index] == '\"')
		{
			quoted = extract_quote(read_line, &index);
			if (quoted)
			{
				printf("* %s\n", quoted);
				free(quoted); // Libera la memoria allocata da ft_substr
			}
		}
		else if ((operator = extract_operator(read_line, &index)))
		{
			printf("[ %s\n", operator);
			free(operator); // Libera la memoria allocata da ft_substr
		}
		else
		{
			word = extract_word(read_line, &index);
			if (word)
			{
				printf("- %s\n", word);
				free(word); // Libera la memoria allocata da ft_substr
			}
		}
	}
	free(read_line); // Libera la memoria allocata da readline
	return (0);
}
