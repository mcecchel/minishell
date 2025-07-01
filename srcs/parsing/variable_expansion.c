/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:00:00 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/01 16:07:32 by mbrighi          ###   ########.fr       */
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
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(getpid()));
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
	if (quote_type == 1)  // Single quotes
		return (0);
	return (1);  // Double quotes or no quotes
}

char	*process_variable(char *str, int *i, t_shell *shell, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*temp;

	(*i)++; // Skip $
	var_name = extract_var_name(str, i);
	if (var_name)
	{
		var_value = handle_special_vars(shell, var_name);
		if (var_value)
		{
			temp = result;
			result = ft_strjoin(result, var_value);
			free(temp);
			if (ft_strcmp(var_name, "?") == 0 || ft_strcmp(var_name, "$") == 0)
				free(var_value);
		}
		free(var_name);
	}
	return (result);
}

char	*process_literal_text(char *str, int *i, char *result)
{
	int		start;
	char	*temp;
	char	*new_result;

	start = *i;
	while (str[*i] && str[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		temp = ft_substr(str, start, *i - start);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
	}
	return (result);
}

char	*expand_variables(char *str, t_shell *shell, int quote_type)
{
	char	*result;
	int		i;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && should_expand_in_quotes(quote_type))
			result = process_variable(str, &i, shell, result);
		else
			result = process_literal_text(str, &i, result);
	}
	return (result);
}
