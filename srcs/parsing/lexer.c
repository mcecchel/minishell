/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/14 17:54:44 by mcecchel         ###   ########.fr       */
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

t_token_type classify_token(char *str, int is_first_token)
{
    if (!str)
        return UNKNOWN;
    // Se il token è racchiuso tra virgolette singole o doppie
    if (str[0] == '\'' && str[strlen(str) - 1] == '\'')
        return QUOTE;
    else if (str[0] == '\"' && str[strlen(str) - 1] == '\"')
        return DQUOTE;
    // Se è il primo token, è un comando
    if (is_first_token)
        return CMD;
    // Controlla se è un'opzione o un flag
    if (str[0] == '-')
        return FLAG;
    // Controlla se è un operatore
    if (ft_strcmp(str, "|") == 0)
        return PIPE;
    else if (ft_strcmp(str, ">") == 0)
        return RED_OUT;
    else if (ft_strcmp(str, "<") == 0)
        return RED_IN;
    else if (ft_strcmp(str, "<<") == 0)
        return HEREDOC;
    else if (ft_strcmp(str, ">>") == 0)
        return APPEND;
    // Altrimenti è un argomento
    return (ARG);
}

t_token *add_token(t_token *token, char *content)
{
	t_token	*new_token;

	if (!token)
	{
		ft_printf("Error: Token list is NULL\n");
		return (NULL);
	}
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (NULL);
	}
	new_token->value = content;
	new_token->type = classify_token(content, 0);
	new_token->next = NULL;
	if (token->head == NULL)
		token->head = new_token;
	else
	{
		token->current = token->head;
		// Trova l'ultimo nodo
		while (token->current->next != NULL)
			token->current = token->current->next;
		token->current->next = new_token;
	}
	return (new_token);
}

t_token *tokenize_input(t_token *token, char *line)
{
    int i = 0;
    int is_first_token = 1; // Flag per identificare il primo token

    token->head = NULL;
    token->current = NULL;

    while (line[i])
    {
        while (is_space(line[i]))
            i++;
        if (line[i] == '\0')
            break;
        char *content = NULL;
        // Gestione quote
        if (line[i] == '\'' || line[i] == '\"')
            content = extract_quote(line, &i);
        // Gestione operatori
        else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
            content = extract_operator(line, &i);
        // Gestione parole
        else
            content = extract_word(line, &i);
        if (content)
        {
            // Classifica il token
            t_token_type type = classify_token(content, is_first_token);
            is_first_token = 0; // Dopo il primo token, tutti gli altri sono ARG o altro
            token->current = add_token(token, content);
            token->current->type = type; // Imposta il tipo del token
        }
    }
    return (token);
}

void	print_token_type(t_token *token)
{
	if (token->type == CMD) printf("CMD");
	else if (token->type == ARG) printf("ARG");
	else if (token->type == OPTION) printf("OPTION");
	else if (token->type == FLAG) printf("FLAG");
	else if (token->type == PIPE) printf("PIPE");
	else if (token->type == RED_IN) printf("RED_IN");
	else if (token->type == RED_OUT) printf("RED_OUT");
	else if (token->type == APPEND) printf("APPEND");
	else if (token->type == HEREDOC) printf("HEREDOC");
	else if (token->type == QUOTE) printf("QUOTE");
	else if (token->type == DQUOTE) printf("DQUOTE");
	else printf("UNKNOWN");
}

void	debug_tokens(t_token *token)
{
	int i = 0;
	while (token)
	{
		printf("[%d] Token: \"%s\" | Type: ", i, token->value);
		print_token_type(token);
		printf("\n");
		token = token->next;
		i++;
	}
}

void	free_tokens(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*cmd_list;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	current_cmd = NULL;
	while (token)
	{
		if (token->type == CMD)
		{
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				return (NULL);
			new_cmd->cmd_path = ft_strdup(token->value);
			new_cmd->argv = malloc(sizeof(char *) * 100); // Allocate memory for argv
			if (!new_cmd->argv)
			{
				ft_printf("Error: Memory allocation failed for argv\n");
				free(new_cmd);
				return (NULL);
			}
			new_cmd->argv[0] = NULL; // Initialize the first element to NULL
			new_cmd->argv[0] = ft_strdup(token->value);
			new_cmd->infile = -1;
			new_cmd->outfile = -1;
			new_cmd->pid = -1;
			new_cmd->next = NULL;
			if (!cmd_list)
				cmd_list = new_cmd;
			else
			{
				current_cmd->next = new_cmd;
				current_cmd = new_cmd;
			}
		}
		else if (token->type == ARG || token->type == FLAG)
		{
			int	i;

			i = 0;
			while (current_cmd->argv[i])
				i++;
			current_cmd->argv[i] = ft_strdup(token->value);
			current_cmd->argv[i + 1] = NULL;
		}
		else if (token->type == PIPE)
		{
			// really dunno
		}
		else if (token->type == RED_IN)
		{
			current_cmd->infile = open(token->next->value, O_RDONLY);
			if (current_cmd->infile < 0)
				perror("Error opening infile");
		}
		else if (token->type == RED_OUT || token->type == APPEND)
		{
			current_cmd->outfile = open(token->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (current_cmd->outfile < 0)
				perror("Error opening outfile");
		}
		else if (token->type == HEREDOC)
		{
			current_cmd->infile = open(token->next->value, O_RDONLY);
			if (current_cmd->infile < 0)
				perror("Error opening heredoc");
		}
		token = token->next;
	}
	return (cmd_list);
}
void	free_cmd_list(t_cmd *cmd)
{
	t_cmd *tmp;
	while (cmd)
	{
		tmp = cmd;
		free(cmd->cmd_path);
		if (cmd->argv)
		{
			for (int i = 0; cmd->argv[i]; i++)
				free(cmd->argv[i]);
			free(cmd->argv);
		}
		cmd = cmd->next;
		free(tmp);
	}
}
