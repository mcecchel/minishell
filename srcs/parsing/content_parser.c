/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   content_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:44:53 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:08:16 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content(char *line, int *i, int *is_quoted, t_shell *shell)
{
	char	*content;
	char	*tmp;
	int		tmp_quoted;

	content = NULL;
	*is_quoted = 0;
	tmp_quoted = 0;
	while (line[*i] && !is_space(line[*i]) && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
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

char	*get_next_piece(char *line, int *i, int *quoted, t_shell *shell)
{
	if (line[*i] == '\'' || line[*i] == '"')
		return (extract_quote(line, i, quoted, shell));
	return (extract_word(line, i, shell));
}

char	*append_content(char *content, char *tmp)
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

void	update_state(t_token_type type, int *is_first, int *waiting)
{
	if (type == PIPE)
	{
		*is_first = 1;
		*waiting = 0;
	}
	else if (type == HEREDOC || type == RED_IN || type == RED_OUT
		|| type == APPEND)
		*waiting = 1;
	else if (*waiting)
		*waiting = 0;
	else if (*is_first)
		*is_first = 0;
}

void	expand_or_not(t_extract_ctx *ctx, t_shell *shell)
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
