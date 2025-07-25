/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:00:00 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/24 16:21:50 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_shell *shell, char *var_name)
{
	t_env	*env;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

char	*handle_special_vars(t_shell *shell, char *var_name)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_value));
	return (get_env_value(shell, var_name));
}

char	*extract_var_name(char *str, int *index)
{
	int		start;
	int		len;
	char	*var_name;

	start = *index;
	if (str[*index] == '?')
	{
		(*index)++;
		return (ft_strdup("?"));
	}
	if (str[*index] == '$')
	{
		(*index)++;
		return (ft_strdup("$"));
	}
	while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
		(*index)++;
	len = *index - start;
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, start, len);
	return (var_name);
}

int	should_expand_in_quotes(int quote_type)
{
	if (quote_type == 1)
		return (0);
	return (1);
}
char	*surround_with_quotes(char *str);

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

static char	*append_dollar(t_expand_ctx *ctx)
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

static char	*append_var_value(t_expand_ctx *ctx, char *var_value)
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

char	*process_variable(t_expand_ctx *ctx)
{
	char	*var_name;
	char	*var_value;
	int		next;

	next = *(ctx->i) + 1;
	if (!ctx->str[next] || is_space(ctx->str[next]) || ctx->str[next] == '\''
		|| ctx->str[next] == '"' || ctx->str[next] == '$'
		|| ctx->str[next] == '|' || (ctx->str[*(ctx->i)] == '$'
			&& is_preceded_by_heredoc(ctx->str, *(ctx->i) - 1)))
		return (append_dollar(ctx));
	(*(ctx->i))++;
	var_name = extract_var_name(ctx->str, ctx->i);
	if (!var_name)
		return (ctx->result);
	var_value = handle_special_vars(ctx->shell, var_name);
	if (var_value && ft_strcmp(var_name, "?") && ft_strcmp(var_name, "$"))
		var_value = ft_strdup(var_value);
	if (!var_value)
		return (free(var_name), NULL);
	if (ctx->initial && !ctx->quote)
		var_value = surround_with_quotes(var_value);
	ctx->result = append_var_value(ctx, var_value);
	free(var_name);
	return (ctx->result);
}

static void	advance_var_name(char *str, int *i)
{
	if (str[*i] == '_' || ft_isalpha(str[*i]))
		(*i)++;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
}

static char	*append_substr_to_result(char *str, int start, int end, char *res)
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

int	next_quote_idx(char *str, int i)
{
	char	quote;
	int		idx;

	idx = i + 1;
	quote = str[idx];
	while (str[idx])
	{
		if (str[idx] == quote)
			return (idx);
		idx++;
	}
	return (-1);
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

static char	update_quote_state(char c, char curr)
{
	if (is_quote(c) && !curr)
		return (c);
	if (is_quote(c) && curr == c)
		return (0);
	return (curr);
}

static char	*append_char(char *result, char c)
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

static char	*process_loop(t_expand_ctx *ctx)
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

char	*expand_variables(char *str, t_shell *shell,
						int quote_type, int initial_parse)
{
	t_expand_ctx	ctx;
	int				i;

	if (!str || !should_expand_in_quotes(quote_type))
		return (ft_strdup(str));
	ctx.str = str;
	ctx.shell = shell;
	ctx.result = ft_strdup("");
	if (!ctx.result)
		return (free(ctx.result), NULL);
	i = 0;
	ctx.i = &i;
	ctx.initial = initial_parse;
	ctx.quote = 0;
	return (process_loop(&ctx));
}
