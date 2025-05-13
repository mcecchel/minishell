/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/13 17:15:58 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char *extract_quote(t_shell shell, char *line, int *index)
{
	char	quote;
	int		start_quote;
	char	*str;

	str = NULL;
	quote = line[*index];
	(*index)++;// Salto  le quote iniziali
	shell.in_quote = 1;
	start_quote = *index;
	while (line[*index] && line[*index] != quote)
		(*index)++;
	if (line[*index] == quote)
	{
		str = ft_substr(line, start_quote, (*index) - start_quote);
		(*index)++;// Salto le quote finali
		shell.in_quote = 0;
	}
	else
		ft_printf("Error: Missing closing quote\n");
		// mettere exit
	return (str);
}

char *extract_operator(char *line, int *index)
{
    int start = *index;

    // Gestisce operatori singoli o doppi (<<, >>)
    if ((line[*index] == '<' && line[*index + 1] == '<') || (line[*index] == '>' && line[*index + 1] == '>'))
        *index += 2; // Salta gli operatori doppi
    else if (line[*index] == '|' || line[*index] == '<' || line[*index] == '>')
        (*index)++; // Salta l'operatore singolo
    else
        return (NULL); // Non è un operatore
    // Estrae l'operatore
    return ft_substr(line, start, *index - start);
}

// 1) Alloca un nuovo nodo token
// 2) Determina il tipo (es: "|" → PIPE, ">" → RED_OUT)
// 3) Lo inserisce in coda alla lista
t_token_type classify_token(t_shell shell, char *str)
{
    // str = NULL;
	if (access(str, X_OK))
		return CMD; // Se il file esiste o è eseguibile è un comando
	if (!str)
		return UNKNOWN;
    if (ft_strcmp(str, "|") == 0 && shell.in_quote == 0)
	{	printf("[%s]\n", str);
        return PIPE;}
    else if (ft_strcmp(str, ">") == 0 && shell.in_quote == 0)
	{	printf("[%s]\n", str);
        return RED_OUT;}
    else if (ft_strcmp(str, "<") == 0&& shell.in_quote == 0)
	{	printf("[%s]\n", str);
		return RED_IN;}
    else if (ft_strcmp(str, "<<") == 0 && shell.in_quote == 0)
	{	printf("[%s]\n", str);
        return HEREDOC;}
    else if (ft_strcmp(str, ">>") == 0 && shell.in_quote == 0)
	{	printf("[%s]\n", str);
        return APPEND;}
    else if (str[0] == '-')
	{	printf("[%s]\n", str);
		return FLAG;}
    else if (str[0] == '\'' || str[0] == '\"')
	{	printf("[%s]\n", str);
        return QUOTE;}
    else
	{
		printf("[%s]\n", str);
			return ARG; // Altrimenti è un argomento
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

int main(void)
{
    char *read_line;
    int index = 0;
    char *token_value;
    t_token token;
	t_shell shell = {0};

    // Inizializza la lista dei token
    token.head = NULL;
    // Legge una riga di input
    read_line = readline("Prompt > ");
    if (!read_line)
        return (1);
    printf("Input line: %s\n", read_line);
    printf("Classified tokens:\n");
    while (read_line[index])
    {
        // Salta gli spazi
        while (read_line[index] && is_space(read_line[index]))
            index++;
        if (read_line[index] == '\0')
            break;
        // Estrae e classifica i token
        if (read_line[index] == '\'' || read_line[index] == '\"')
            token_value = extract_quote(shell, read_line, &index);
        else if ((token_value = extract_operator(read_line, &index)))
        {
            // Gli operatori vengono già estratti
        }
        else
            token_value = extract_word(read_line, &index);
        if (token_value)
        {
            // Classifica il token
            t_token_type type = classify_token(shell, token_value);
            printf("- Value: %s, Type: %d\n", token_value, type);
            // Libera la memoria allocata per il token
            free(token_value);
        }
    }
    // Libera la memoria allocata per la riga
    free(read_line);
    return (0);
}

t_token *add_token(t_shell shell, char *content)
{
	t_token	*new_token;
	t_token	*current;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = content;
	new_token->type = classify_token(shell, content);
	new_token->next = NULL;
	if (shell.token.head == NULL)
		shell.token.head = new_token;
	else
	{
		current = shell.token.head;
		// Trova l'ultimo nodo
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	return (new_token);
}

// int main()
// {
// 	char *read_line;
// 	int index = 0;
// 	char *word;
// 	char *operator;
// 	char *quoted;

// 	read_line = readline("Prompt > ");
// 	printf("%s\n", read_line);

// 	printf("Input line: %s\n", read_line);
// 	printf("Extracted tokens:\n");
// 	while (read_line[index])
// 	{
// 		while (read_line[index] && is_space(read_line[index]))
// 			index++;
// 		if (read_line[index] == '\0')
// 			break;
// 		if (read_line[index] == '\'' || read_line[index] == '\"')
// 		{
// 			quoted = extract_quote(read_line, &index);
// 			if (quoted)
// 			{
// 				printf("* %s\n", quoted);
// 				free(quoted); // Libera la memoria allocata da ft_substr
// 			}
// 		}
// 		else if ((operator = extract_operator(read_line, &index)))
// 		{
// 			printf("[ %s\n", operator);
// 			free(operator); // Libera la memoria allocata da ft_substr
// 		}
// 		else
// 		{
// 			word = extract_word(read_line, &index);
// 			if (word)
// 			{
// 				printf("- %s\n", word);
// 				free(word); // Libera la memoria allocata da ft_substr
// 			}
// 		}
// 	}
// 	free(read_line); // Libera la memoria allocata da readline
// 	return (0);
// }
