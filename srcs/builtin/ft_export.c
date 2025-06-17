/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:45:25 by mbrighi           #+#    #+#             */
/*   Updated: 2025/06/17 15:10:26 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(t_env *env, char *name, char *value, bool is_env)
{
	while (env)
	{
		if (ft_strcmp(env->var, name) == 0)
		{
			if (env->arg)
				free(env->arg);
			env->arg = value;
			env->ex_env = 0;
			if (is_env)
				env->ex_env = 1;
			free(name);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static void	add_new_env(t_shell *root, char *name, char *value, bool is_env)
{
	t_env	*new_env;

	new_env = ft_calloc(1, sizeof(t_env));
	new_env->var = name;
	new_env->arg = value;
	new_env->ex_env = 0;
	if (is_env)
		new_env->ex_env = 1;
	new_env->next = root->env;
	if (root->env)
		root->env->prev = new_env;
	new_env = sort_env_list(new_env);
	root->env = new_env;
}

void	add_env(t_shell *root, char *arg, bool is_env)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	value = NULL;
	if (arg[i] == '=')
		value = ft_strdup(arg + i + 1);
	if (update_env(root->env, name, value, is_env))
		return ;
	add_new_env(root, name, value, is_env);
}

void	ft_export(t_shell *root)
{
	int i;

	i = 1;
	if (root->cmd->argc == 1)
	{
		print_env_list(root->env, false);
		return ;
	}
	while (root->cmd->argv[i] != NULL)
	{
		if (ft_strchr(root->cmd->argv[i], '='))
			add_env(root, root->cmd->argv[i], true);
		else
			add_env(root, root->cmd->argv[i], false);
		i++;
	}
}
