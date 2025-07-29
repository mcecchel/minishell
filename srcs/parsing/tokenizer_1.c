/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:55:02 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:08:41 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_tokens(t_parse *p)
{
	while (p->line[p->i])
	{
		while (is_space(p->line[p->i]))
			p->i++;
		if (p->line[p->i] == '\0')
			break ;
		if (p->line[p->i] == '|' || p->line[p->i] == '<'
			|| p->line[p->i] == '>')
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

int	handle_operator(t_parse *p)
{
	char	*op;

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
