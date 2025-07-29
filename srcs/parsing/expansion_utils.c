/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:33:51 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/28 17:35:21 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	should_expand_in_quotes(int quote_type)
{
	if (quote_type == 1)
		return (0);
	return (1);
}

char	*process_literal_text(char *str, int *i, char *result)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (str[*i] == '$')
		(*i)++;
	advance_var_name(str, i);
	if (*i > start)
		result = append_substr_to_result(str, start, *i, result);
	return (result);
}

char	*append_dollar(t_expand_ctx *ctx)
{
	char	*temp;
	char	*new_result;

	temp = ctx->result;
	new_result = ft_strjoin(ctx->result, "$");
	if (new_result)
	{
		free(temp);
		ctx->result = new_result;
	}
	(*(ctx->i))++;
	return (ctx->result);
}

char	*append_var_value(t_expand_ctx *ctx, char *var_value)
{
	char	*temp;
	char	*new_result;

	temp = ctx->result;
	new_result = ft_strjoin(ctx->result, var_value);
	free(var_value);
	if (new_result)
	{
		free(temp);
		ctx->result = new_result;
	}
	return (ctx->result);
}

void	advance_var_name(char *str, int *i)
{
	if (str[*i] == '_' || ft_isalpha(str[*i]))
		(*i)++;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
}
