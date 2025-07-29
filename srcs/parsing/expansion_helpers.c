/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:35:40 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 17:38:08 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_substr_to_result(char *str, int start, int end, char *res)
{
	char	*temp;
	char	*new_result;

	temp = ft_substr(str, start, end - start);
	if (!temp)
		return (res);
	new_result = ft_strjoin(res, temp);
	free(temp);
	if (new_result)
	{
		free(res);
		return (new_result);
	}
	return (res);
}

char	update_quote_state(char c, char curr)
{
	if (is_quote(c) && !curr)
		return (c);
	if (is_quote(c) && curr == c)
		return (0);
	return (curr);
}

char	*append_char(char *result, char c)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(result);
	temp = ft_calloc(len + 2, sizeof(char));
	if (!temp)
		return (NULL);
	ft_memmove(temp, result, len);
	temp[len] = c;
	free(result);
	return (temp);
}

char	*process_loop(t_expand_ctx *ctx)
{
	char	*temp;

	while (ctx->str && ctx->str[*(ctx->i)])
	{
		ctx->quote = update_quote_state(ctx->str[*(ctx->i)], ctx->quote);
		if (ctx->str[*(ctx->i)] == '$'
			&& (!ctx->initial || ctx->quote != '\''))
		{
			temp = process_variable(ctx);
			if (!temp)
				return (free(ctx->result), NULL);
			ctx->result = temp;
		}
		else
		{
			temp = append_char(ctx->result, ctx->str[*(ctx->i)]);
			if (!temp)
				return (NULL);
			ctx->result = temp;
			(*(ctx->i))++;
		}
	}
	return (ctx->result);
}

int	handle_token_in_loop(t_token **tok, t_cmd **cmd_list,
				t_cmd **current, t_shell *shell)
{
	if ((*tok)->type == CMD)
		return (handle_cmd_advance(tok, cmd_list, current, shell));
	else if (is_redirection_token((*tok)->type))
		return (handle_redirection_advance(tok, cmd_list, current, shell));
	else
		return (handle_standard_advance(tok, cmd_list, current, shell));
}
