/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 20:34:40 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:07:02 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_word(char *line, int *index, t_shell *shell)
{
	t_extract_ctx	ctx;
	int				start;
	int				end;

	start = *index;
	end = start;
	while (line[end] && !is_space(line[end])
		&& line[end] != '|' && line[end] != '>' && line[end] != '<'
		&& line[end] != '\'' && line[end] != '\"')
		end++;
	ctx.res = ft_substr(line, start, end - start);
	if (!ctx.res)
		return (*index = end, NULL);
	*index = end;
	if (should_expand_word(shell))
	{
		ctx.expanded = expand_variables(ctx.res, shell, 0, 0);
		free(ctx.res);
		return (ctx.expanded);
	}
	return (ctx.res);
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
