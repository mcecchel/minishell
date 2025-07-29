/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:51:58 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:05:22 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(t_token *token_list, char **l, t_shell *shell)
{
	t_parse	p;

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

const char	*obtain_token_type(t_token *token)
{
	if (!DEBUG)
		return ("NULL");
	if (token->type == CMD)
		return ("CMD");
	else if (token->type == ARG)
		return ("ARG");
	else if (token->type == FLAG)
		return ("FLAG");
	else if (token->type == PIPE)
		return ("PIPE");
	else if (token->type == RED_IN)
		return ("RED_IN");
	else if (token->type == RED_OUT)
		return ("RED_OUT");
	else if (token->type == APPEND)
		return ("APPEND");
	else if (token->type == HEREDOC)
		return ("HEREDOC");
	else if (token->type == QUOTE)
		return ("QUOTE");
	else if (token->type == DQUOTE)
		return ("DQUOTE");
	else
		return ("UNKNOWN");
}

int	should_expand_word(t_shell *shell)
{
	t_token	*lst;

	if (!shell->token.head)
		return (1);
	lst = ft_last(shell->token.head);
	return (!lst || lst->type != HEREDOC);
}
