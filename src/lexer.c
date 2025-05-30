/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/05/30 19:14:48 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Estrae una parola fino a uno spazio / operatore
char	*extract_word(char *line, int *index)
{
	char *word;
	int start;
	int end;

	start = *index;
	end = start;
	// Incrementa `end` fino a uno spazio o un operatore
	while (line[end] && !is_space(line[end]) &&
		line[end] != '|' && line[end] != '>' && line[end] != '<' &&
		line[end] != '\'' && line[end] != '\"')
			end++;
	word = ft_substr(line, start, end - start);
	if (!word)
	{
		*index = end;
		return (NULL);
	}
	*index = end;
	return (word);
}

char *extract_quote(char *line, int *index, int *is_quoted)
{
    char quote_char = line[*index];
    int start = *index + 1;
    int end = start;
    char *result;
    
    *is_quoted = 1;
    // Trova la quote di chiusura
    while (line[end] && line[end] != quote_char)
        end++; 
    if (line[end] != quote_char)
    {
        ft_printf("minishell: syntax error: unclosed quote\n");
        *is_quoted = 0;
        return (NULL);
    }
    result = ft_substr(line, start, end - start);
    if (!result)
        return (NULL);
        
    *index = end + 1;
    return (result);
}

char *extract_operator(char *line, int *index)
{
    int start = *index;
    // Gestisce operatori singoli o doppi (<<, >>)
    if ((line[*index] == '<' && line[*index + 1] == '<') || 
        (line[*index] == '>' && line[*index + 1] == '>'))
        *index += 2; // Salta gli operatori doppi
    else if (line[*index] == '|' || line[*index] == '<' || line[*index] == '>')
        (*index)++; // Salta l'operatore singolo
    else
        return (NULL); // Non è un operatore
    return ft_substr(line, start, *index - start);
}

// Classificazione token migliorata
t_token_type classify_token(char *str, int is_first_token, int is_quoted)
{
    if (!str)
        return UNKNOWN;
    // Se è quotato, determina il tipo in base al contesto
    if (is_quoted)
    {
        if (is_first_token)
            return CMD;
        else
            return ARG;
    }
    // Controlla operatori (solo se non quotato)
    if (ft_strcmp(str, "|") == 0) return PIPE;
    if (ft_strcmp(str, ">") == 0) return RED_OUT;
    if (ft_strcmp(str, "<") == 0) return RED_IN;
    if (ft_strcmp(str, "<<") == 0) return HEREDOC;
    if (ft_strcmp(str, ">>") == 0) return APPEND;
    // Se è il primo token, è un comando
    if (is_first_token)
        return CMD;
    // Se inizia con '-' ed ha altri caratteri, è un flag
    if (str[0] == '-' && str[1] != '\0')
        return FLAG;
    // Altrimenti è un argomento
    return ARG;
}

t_token *create_token(char *content, t_token_type type, int is_quoted)
{
    t_token *new_token;

    new_token = ft_calloc(1, sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->value = content; // Il content è già allocato
    new_token->type = type;
    new_token->is_quoted = is_quoted;
    new_token->next = NULL;
    return (new_token);
}

// Funzione per aggiungere token alla lista
void add_token_to_list(t_token *token_list, t_token *new_token)
{
    if (!token_list->head)
    {
        token_list->head = new_token;
        token_list->current = new_token;
    }
    else
    {
        token_list->current->next = new_token;
        token_list->current = new_token;
    }
}

// Tokenizer principale - VERSIONE CORRETTA
int tokenize_input(t_token *token_list, char *line)
{
    int i;
    int is_first_token;

    i = 0;
    is_first_token = 1;
    // Inizializza la lista
    token_list->head = NULL;
    token_list->current = NULL;
    while (line[i])
    {
        // Salta spazi bianchi
        while (is_space(line[i]))
            i++;
        if (line[i] == '\0')
            break;

        char *content = NULL;
        int is_quoted = 0;
        // Gestione quote
        if (line[i] == '\'' || line[i] == '\"')
        {
            content = extract_quote(line, &i, &is_quoted);
            if (!content) // Errore nelle quote
            {
                free_tokens(token_list->head);
                token_list->head = NULL;
                return (0);
            }
        }
        // Gestione operatori
        else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
        {
            content = extract_operator(line, &i);
            if (!content)
            {
                free_tokens(token_list->head);
                token_list->head = NULL;
                return (0);
            }
        }
        // Gestione parole normali
        else
        {
            content = extract_word(line, &i);
            if (!content)
            {
                free_tokens(token_list->head);
                token_list->head = NULL;
                return (0);
            }
        }
        // Classifica e crea il token
        t_token_type type = classify_token(content, is_first_token, is_quoted);
        t_token *new_token = create_token(content, type, is_quoted);
        if (!new_token)
        {
            free(content);
            free_tokens(token_list->head);
            token_list->head = NULL;
            return (0);
        }
        // Aggiungi alla lista
        add_token_to_list(token_list, new_token);
        // Aggiorna il flag per il primo token
        if (type == PIPE)
            is_first_token = 1; // Reset dopo pipe
        else if (is_first_token)
            is_first_token = 0; // Non più il primo token
    }
    return (1); // Successo
}

// Funzione di debug 1
void	print_token_type(t_token *token)
{
	if (token->type == CMD) printf("CMD");
	else if (token->type == ARG) printf("ARG");
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

// Funzione di debug 2
void	debug_tokens(t_token *token)
{
	int i = 0;
	while (token)
	{
		printf("[%d] Token: \"%s\" | Type: ", i, token->value);
		print_token_type(token);
		if (token->is_quoted)
			printf(" (QUOTED)");
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

int handle_heredoc(char *delimiter)
{
    int pipe_fd[2];
    char *line;

    // Crea una pipe per salvare l'input dell'heredoc
    if (pipe(pipe_fd) < 0)
    {
        perror("pipe");
        return (-1);
    }
    // Legge da stdin fino al delimitatore
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            close(pipe_fd[1]);
            return (pipe_fd[0]);
        }
        // Se la linea è uguale al delimitatore, termina
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        // Scrivi nella pipe e aggiungi un newline
        ft_putendl_fd(line, pipe_fd[1]);
        free(line);
    }
    close(pipe_fd[1]);
    return (pipe_fd[0]);
}

void debug_cmds(t_cmd *cmd_list)
{
    int cmd_index = 0;
    t_cmd *current = cmd_list;

    while (current)
    {
        printf("Command %d:\n", cmd_index++);
        printf("  Path: %s\n", current->cmd_path);
        printf("  Arguments: ");
        int i = 0;
        while (current->argv && current->argv[i])
        {
            printf("\"%s\" ", current->argv[i]);
            i++;
        }
        printf("\n");
        printf("  Infile: %d\n", current->infile);
        printf("  Outfile: %d\n", current->outfile);
        current = current->next;
    }
}

void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;
    
    while (cmd)
    {
        tmp = cmd;
        cmd = cmd->next;
        if (tmp->cmd_path)
            free(tmp->cmd_path);
        if (tmp->argv)
        {
            int i = 0;
            while (tmp->argv[i])
            {
                free(tmp->argv[i]);
                i++;
            }
            free(tmp->argv);
        }
        if (tmp->infile != -1)
            close(tmp->infile);
        if (tmp->outfile != -1)
            close(tmp->outfile);
            
        free(tmp);
    }
}
