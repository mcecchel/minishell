/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:30:03 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 17:41:49 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env(t_env *env, char *name, char *value, int type)
{
	while (env)
	{
		if (ft_strcmp(env->var, name) == 0)
		{
			if (env->arg)
				free(env->arg);
			env->arg = value;
			env->ex_env = 0;
			if (type == ENV)
				env->ex_env = 1;
			free(name);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_new_env(t_shell *root, char *name, char *value, int type)
{
	t_env	*new_env;
	t_env	*sorted_env;

	new_env = ft_calloc(1, sizeof(t_env));
	if (!new_env)
	{
		free(name);
		free(value);
		return ;
	}
	new_env->var = name;
	new_env->arg = value;
	new_env->ex_env = 0;
	if (type == ENV)
		new_env->ex_env = 1;
	if (type == VAR)
		new_env->ex_env = 2;
	new_env->next = root->env;
	if (root->env)
		root->env->prev = new_env;
	sorted_env = sort_env_list(new_env);
	if (sorted_env)
		root->env = sorted_env;
	else
		root->env = new_env;
}

static char	*extract_name(char *arg, int *equal_pos)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	*equal_pos = i;
	name = ft_substr(arg, 0, i);
	return (name);
}

static char	*extract_value(char *arg, int equal_pos, char *name)
{
	char	*value;

	value = NULL;
	if (arg[equal_pos] == '=')
	{
		value = ft_strdup(arg + equal_pos + 1);
		if (!value)
		{
			free(name);
			return (NULL);
		}
	}
	return (value);
}

void	add_env(t_shell *root, char *arg, int type)
{
	char	*name;
	char	*value;
	int		equal_pos;

	name = extract_name(arg, &equal_pos);
	if (!name)
		return ;
	value = extract_value(arg, equal_pos, name);
	if (equal_pos != 0 && arg[equal_pos] == '=' && !value)
		return ;
	if (update_env(root->env, name, value, type))
	{
		update_shell_envp(root);
		return ;
	}
	add_new_env(root, name, value, type);
	update_shell_envp(root);
}
