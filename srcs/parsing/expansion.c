/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:30:31 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/29 15:06:04 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_variables(char *str, t_shell *shell, int quote_type,
						int initial_parse)
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

char	*handle_special_vars(t_shell *shell, char *var_name)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_value));
	return (get_env_value(shell, var_name));
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
		return (free(var_name), ctx->result);
	if (ctx->initial && !ctx->quote)
		var_value = surround_with_quotes(var_value);
	ctx->result = append_var_value(ctx, var_value);
	free(var_name);
	return (ctx->result);
}
