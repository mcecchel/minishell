/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:12:46 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 21:08:57 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_preceded_by_heredoc(char *str, int i)
{
	int	j;

	j = i - 1;
	while (j >= 0 && is_space(str[j]))
		j--;
	if (j < 0)
		return (0);
	if (j >= 1 && str[j] == '<' && str[j - 1] == '<')
		return (1);
	return (0);
}

void	find_closing_quote(t_extract_ctx *ctx, char *line)
{
	int	i;

	i = ctx->start;
	while (line[i] && line[i] != ctx->quote_char)
		i++;
	ctx->end = i;
}

char	*surround_with_quotes(char *str)
{
	int		i;
	char	*new_str;
	char	quote;

	i = 0;
	while (str[i])
	{
		if (is_special(str[i]))
		{
			new_str = ft_calloc(ft_strlen(str) + 3, sizeof(char));
			if (!new_str)
				return (free(str), NULL);
			ft_memmove(new_str, str, i);
			quote = ("'\"")[str[i] != '"'];
			new_str[i] = quote;
			new_str[i + 1] = str[i];
			new_str[i + 2] = quote;
			ft_memmove(new_str + i + 3, str + i + 1, ft_strlen(str + i));
			free(str);
			str = new_str;
			i += 2;
		}
		i++;
	}
	return (str);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

bool	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' || is_quote(c));
}
