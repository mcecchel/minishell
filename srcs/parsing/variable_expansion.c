/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 16:00:00 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/19 19:00:23 by mcecchel         ###   ########.fr       */
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

char	*process_variable(char *str, int *i, t_shell *shell, char *result)
{
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*new_result;
	int		next;

	var_name = NULL;
	var_value = NULL;
	temp = NULL;
	new_result = NULL;
	next = *i + 1;
	if (!str[next] || is_space(str[next]) || str[next] == '\''
		|| str[next] == '"' || str[next] == '$' || str[next] == '|')
	{
		temp = result;
		new_result = ft_strjoin(result, "$\0");
		if (new_result)
		{
			free(temp);
			result = new_result;
		}
		else
			result = temp;
		(*i)++;
		return (result);
	}
	(*i)++;
	var_name = extract_var_name(str, i);
	if (var_name)
	{
		var_value = handle_special_vars(shell, var_name);
		if (var_value)
		{
			temp = result;
			new_result = ft_strjoin(result, var_value);
			if (new_result)
			{
				free(temp);
				result = new_result;
			}
			else
			{
				result = temp;
			}
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
	if (str[*i] == '$')
		(*i)++;
	if (str[*i] == '_' || ft_isalpha(str[*i]))
		(*i)++;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	if (*i >= start)
	{
		temp = ft_substr(str, start, *i - start);
		if (!temp)
			return (result);
		new_result = ft_strjoin(result, temp);
		free(temp);
		if (new_result)
		{
			free(result);
			result = new_result;
		}
	}
	return (result);
}

char	*expand_variables(char *str, t_shell *shell, int quote_type)
{
	char	*result;
	char	*temp;
	int		i;

	if (!str)
		return (NULL);
	if (!should_expand_in_quotes(quote_type))
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			temp = process_variable(str, &i, shell, result);
			if (!temp)
				return (free(result), NULL);
			result = temp;
		}
		else
		{
			temp = ft_calloc(ft_strlen(result) + 2, sizeof(char));
			if (!temp)
				return (free(result), NULL);
			ft_memmove(temp, result, ft_strlen(result));
			temp[ft_strlen(result)] = str[i];
			free(result);
			result = temp;
			i++;
		}
	}
	return (result);
}
