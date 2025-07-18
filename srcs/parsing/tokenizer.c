/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/18 17:43:41 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Estrae una parola fino a uno spazio / operatore
char	*extract_word(char *line, int *index, t_shell *shell)
{
	char			*word;
	char			*expanded;
	int				start;
	int				end;
	t_token			*lst;

	start = *index;
	end = start;
	expanded = NULL;
	while (line[end] && !is_space(line[end])
		&& line[end] != '|' && line[end] != '>' && line[end] != '<'
		&& line[end] != '\'' && line[end] != '\"')
		end++;
	word = ft_substr(line, start, end - start);
	if (!word)
	{
		*index = end;
		return (NULL);
	}
	*index = end;
	expanded = word;
	lst = NULL;
	if (shell->token.head)
		lst = ft_last(shell->token.head);
	if (!lst || lst->type != HEREDOC)
	{
		expanded = expand_variables(word, shell, 0);
		free(word);
	}
	return (expanded);
}

char *extract_quote(char *line, int *index, int *is_quoted, t_shell *shell)
{
	char	quote_char = line[*index];
	int		start = *index + 1;
	int		end = start;
	char	*res;
	char	*expanded;
	int		quote_type;
	t_token	*lst;

	expanded = NULL;
	*is_quoted = 1;
	while (line[end] && line[end] != quote_char)
		end++;
	if (line[end] != quote_char)
	{
		ft_printf("minishell: syntax error: unclosed quote\n");
		*is_quoted = 0;
		return (NULL);
	}
	res = ft_substr(line, start, end - start);
	if (!res)
		return (NULL);
	*index = end + 1;
	if (quote_char == '\'')
		quote_type = 1;
	else
		quote_type = 2;
	lst = NULL;
	if (shell->token.head)
		lst = ft_last(shell->token.head);
	expanded = res;
	if (!lst || lst->type != HEREDOC)
	{
		expanded = expand_variables(res, shell, quote_type);
		free(res);
	}
	return (expanded);
}

char	*extract_operator(char *line, int *index)
{
	int	start;

	start = *index;
	if ((line[*index] == '<' && line[*index + 1] == '<')
		|| (line[*index] == '>' && line[*index + 1] == '>'))
		*index += 2;
	else if (line[*index] == '|' || line[*index] == '<' || line[*index] == '>')
		(*index)++;
	else
		return (NULL);
	return (ft_substr(line, start, *index - start));
}

// Classificazione token migliorata
t_token_type	classify_token(char *str, int is_first_token, int is_quoted)
{
	if (!str)
		return (UNKNOWN);
	if (is_quoted)
	{
		if (is_first_token)
			return (CMD);
		else
			return (ARG);
	}
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, ">") == 0)
		return (RED_OUT);
	if (ft_strcmp(str, "<") == 0)
		return (RED_IN);
	if (ft_strcmp(str, "<<") == 0)
		return (HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (APPEND);
	if (is_first_token)
		return (CMD);
	if (str[0] == '-' && str[1] != '\0')
		return (FLAG);
	return (ARG);
}

t_token	*create_token(char *content, t_token_type type, int is_quoted)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = content;
	new_token->type = type;
	new_token->is_quoted = is_quoted;
	new_token->next = NULL;
	return (new_token);
}

// Funzione per aggiungere token alla lista
void	add_token_to_list(t_token *token_list, t_token *new_token)
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
int	tokenize_input(t_token *token_list, char *line, t_shell *shell)
{
	int	i = 0;
	int	is_first_token = 1;
	int	waiting_for_redirect_arg = 0;
	token_list->head = NULL;
	token_list->current = NULL;

	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (line[i] == '\0')
			break;

		// Concatenazione quote e testo adiacente
		char *content = NULL;
		int is_quoted = 0;
		while (line[i] && !is_space(line[i]) && line[i] != '|' && line[i] != '<' && line[i] != '>')
		{
			char *tmp = NULL;
			int tmp_quoted = 0;
			if (line[i] == '\'' || line[i] == '\"')
				tmp = extract_quote(line, &i, &tmp_quoted, shell);
			else
				tmp = extract_word(line, &i, shell);

			if (!tmp)
			{
				free(content);
				free_tokens(token_list->head);
				token_list->head = NULL;
				return (0);
			}
			if (tmp_quoted)
				is_quoted = 1;
			if (!content)
				content = tmp;
			else
			{
				char *joined = ft_strjoin(content, tmp);
				free(content);
				free(tmp);
				content = joined;
			}
		}
		if (content)
		{
			t_token_type type = classify_token(content, is_first_token, is_quoted);
			t_token *new_token = create_token(content, type, is_quoted);
			if (!new_token)
			{
				free(content);
				free_tokens(token_list->head);
				token_list->head = NULL;
				return (0);
			}
			add_token_to_list(token_list, new_token);
		if (type == PIPE)
		{
			is_first_token = 1;
			waiting_for_redirect_arg = 0;
		}
		else if (type == HEREDOC || type == RED_IN || type == RED_OUT || type == APPEND)
			waiting_for_redirect_arg = 1;
		else if (waiting_for_redirect_arg)
			waiting_for_redirect_arg = 0; // Non cambiamo is_first_token - il prossimo token potrebbe essere CMD
		else if (is_first_token)
			is_first_token = 0;
		}

		if (line[i] == '|' || line[i] == '<' || line[i] == '>')
		{
			char *op = extract_operator(line, &i);
			if (!op)
			{
				free_tokens(token_list->head);
				token_list->head = NULL;
				return (0);
			}
			t_token_type type = classify_token(op, is_first_token, 0);
			t_token *new_token = create_token(op, type, 0);
			if (!new_token)
			{
				free(op);
				free_tokens(token_list->head);
				token_list->head = NULL;
				return (0);
			}
			add_token_to_list(token_list, new_token);
			if (type == PIPE)
			{
				is_first_token = 1;
				waiting_for_redirect_arg = 0;
			}
			else if (type == HEREDOC || type == RED_IN || type == RED_OUT || type == APPEND)
				waiting_for_redirect_arg = 1;
			else if (waiting_for_redirect_arg)
				waiting_for_redirect_arg = 0;
			else if (is_first_token)
				is_first_token = 0;
		}
	}
	return (1);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}
