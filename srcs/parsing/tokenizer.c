/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:58:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/25 23:13:17 by mbrighi          ###   ########.fr       */
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
		expanded = expand_variables(word, shell, 0, 0);
		free(word);
	}
	return (expanded);
}

// char	*extract_quote(char *line, int *index, int *is_quoted, t_shell *shell)
// {
// 	char	quote_char;
// 	int		start;
// 	int		end;
// 	char	*res;
// 	char	*expanded;
// 	int		quote_type;
// 	t_token	*lst;

// 	quote_char = line[*index];
// 	start = *index + 1;
// 	end = start;
// 	expanded = NULL;
// 	*is_quoted = 1;
// 	while (line[end] && line[end] != quote_char)
// 		end++;
// 	if (line[end] != quote_char)
// 	{
// 		ft_printf("minishell: syntax error: unclosed quote\n");
// 		*is_quoted = 0;
// 		return (NULL);
// 	}
// 	res = ft_substr(line, start, end - start);
// 	if (!res)
// 		return (NULL);
// 	*index = end + 1;
// 	if (quote_char == '\'')
// 		quote_type = 1;
// 	else
// 		quote_type = 2;
// 	lst = NULL;
// 	if (shell->token.head)
// 		lst = ft_last(shell->token.head);
// 	expanded = res;
// 	if (!lst || lst->type != HEREDOC)
// 	{
// 		expanded = expand_variables(res, shell, quote_type, 0);
// 		free(res);
// 	}
// 	return (expanded);
// }

static void	find_closing_quote(t_extract_ctx *ctx, char *line)
{
	int	i;

	i = ctx->start;
	while (line[i] && line[i] != ctx->quote_char)
		i++;
	ctx->end = i;
}

static void	expand_or_not(t_extract_ctx *ctx, t_shell *shell)
{
	t_token	*lst;

	if (!shell->token.head)
	{
		ctx->expanded = ctx->res;
		return ;
	}
	lst = ft_last(shell->token.head);
	if (lst && lst->type == HEREDOC)
		ctx->expanded = ctx->res;
	else
		ctx->expanded = expand_variables(ctx->res, shell, ctx->quote_type, 0);
}

char	*extract_quote(char *line, int *index, int *is_quoted, t_shell *shell)
{
	t_extract_ctx	ctx;

	ctx.quote_char = line[*index];
	ctx.start = *index + 1;
	*is_quoted = 1;
	find_closing_quote(&ctx, line);
	if (line[ctx.end] != ctx.quote_char)
	{
		ft_printf("minishell: syntax error: unclosed quote\n");
		*is_quoted = 0;
		return (NULL);
	}
	ctx.res = ft_substr(line, ctx.start, ctx.end - ctx.start);
	if (!ctx.res)
		return (NULL);
	*index = ctx.end + 1;
	if (ctx.quote_char == '\'')
		ctx.quote_type = 1;
	else
		ctx.quote_type = 2;
	expand_or_not(&ctx, shell);
	if (ctx.expanded != ctx.res)
		free(ctx.res);
	return (ctx.expanded);
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

void	update_state(t_token_type type, int *is_first, int *waiting)
{
	if (type == PIPE)
	{
		*is_first = 1;
		*waiting = 0;
	}
	else if (type == HEREDOC || type == RED_IN || type == RED_OUT || type == APPEND)
		*waiting = 1;
	else if (*waiting)
		*waiting = 0;
	else if (*is_first)
		*is_first = 0;
}

char	*get_next_piece(char *line, int *i, int *quoted, t_shell *shell)
{
	if (line[*i] == '\'' || line[*i] == '"')
		return (extract_quote(line, i, quoted, shell));
	return (extract_word(line, i, shell));
}

char    *append_content(char *content, char *tmp)
{
	char	*joined;

	joined = ft_strjoin(content, tmp);
	if (!joined)
	{
		free(content);
		free(tmp);
		return (NULL);
	}
	free(content);
	free(tmp);
	return (joined);
}

char	*get_content(char *line, int *i, int *is_quoted, t_shell *shell)
{
	char	*content;
	char	*tmp;
	int		tmp_quoted;

	content = NULL;
	*is_quoted = 0;
	tmp_quoted = 0;
	while (line[*i] && !is_space(line[*i]) && line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		tmp = get_next_piece(line, i, &tmp_quoted, shell);
		if (!tmp)
		{
			free(content);
			return (NULL);
		}
		if (tmp_quoted)
			*is_quoted = 1;
		if (!content)
			content = tmp;
		else
			content = append_content(content, tmp);
	}
	return (content);
}

int	add_content_token(t_parse *p, char *content, int is_quoted)
{
	t_token_type	type;
	t_token			*new_token;

	if (p->waiting)
		type = ARG;
	else
		type = classify_token(content, p->is_first, is_quoted);
	new_token = create_token(content, type, is_quoted);
	if (!new_token)
	{
		free(content);
		free_tokens(p->token_list->head);
		p->token_list->head = NULL;
		return (0);
	}
	add_token_to_list(p->token_list, new_token);
	update_state(type, &(p->is_first), &(p->waiting));
	return (1);
}

int	handle_content(t_parse *p)
{
	char	*content;
	int		is_quoted;

	content = get_content(p->line, &(p->i), &is_quoted, p->shell);
	if (!content)
	{
		free_tokens(p->token_list->head);
		p->token_list->head = NULL;
		return (0);
	}
	if (!add_content_token(p, content, is_quoted))
		return (0);
	return (1);
}

int	add_operator_token(t_parse *p, char *op)
{
	t_token_type	type;
	t_token			*new_token;

	type = classify_token(op, p->is_first, 0);
	new_token = create_token(op, type, 0);
	if (!new_token)
	{
		free(op);
		free_tokens(p->token_list->head);
		p->token_list->head = NULL;
		return (0);
	}
	add_token_to_list(p->token_list, new_token);
	update_state(type, &(p->is_first), &(p->waiting));
	return (1);
}

int	handle_operator(t_parse *p)
{
	char    *op;

	op = extract_operator(p->line, &(p->i));
	if (!op)
	{
		free_tokens(p->token_list->head);
		p->token_list->head = NULL;
		return (0);
	}
	if (!add_operator_token(p, op))
		return (0);
	return (1);
}

int	process_tokens(t_parse *p)
{
	while (p->line[p->i])
	{
		while (is_space(p->line[p->i]))
			p->i++;
		if (p->line[p->i] == '\0')
			break ;
		if (p->line[p->i] == '|' || p->line[p->i] == '<' || p->line[p->i] == '>')
		{
			if (!handle_operator(p))
				return (0);
		}
		else
		{
			if (!handle_content(p))
				return (0);
		}
	}
	return (1);
}

int	tokenize_input(t_token *token_list, char **l, t_shell *shell)
{
	t_parse p;

	token_list->head = NULL;
	token_list->current = NULL;

	if (!token_list || !l || !*l || !shell)
		return (0);
	p.token_list = token_list;
	p.shell = shell;
	p.i = 0;
	p.is_first = 1;
	p.waiting = 0;
	p.line = expand_variables(*l, shell, 0, 1);
	if (!p.line)
		return (0);
	free(*l);
	*l = p.line;
	return (process_tokens(&p));
}
