/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:45:25 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/09 16:57:19 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env(t_env *env, char *name, char *value, int type)
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

static void	add_new_env(t_shell *root, char *name, char *value, int type)
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

void	add_env(t_shell *root, char *arg, int type)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	if (!name)
		return ;
	value = NULL;
	if (arg[i] == '=')
	{
		value = ft_strdup(arg + i + 1);
		if (!value)
		{
			free(name);
			return ;
		}
	}
	if (update_env(root->env, name, value, type))
	{
		// Aggiorna envp dopo aver modificato la lista
		update_shell_envp(root);
		return ;
	}
	add_new_env(root, name, value, type);
	// Aggiorna envp dopo aver aggiunto un nuovo environment
	update_shell_envp(root);
}

void	ft_export(t_shell *root)
{
	int i;
	int fd;

	i = 0;
	if (ft_strcmp(root->cmd->argv[0], "export") == 0)
		i = 1;
	if (root->cmd->argc == 1)
	{
		fd = which_fd(root);
		print_env_list_fd(root->env, EXPORT, fd);
		return ;
	}
	while (root->cmd->argv[i] != NULL)
	{
		if (ft_strchr(root->cmd->argv[i], '=')
			&& ft_strcmp(root->cmd->argv[0], "export") == 0)
			add_env(root, root->cmd->argv[i], ENV);
		if (ft_strcmp(root->cmd->argv[0], "export") == 0)
			add_env(root, root->cmd->argv[i], EXPORT);
		if ((ft_strchr(root->cmd->argv[i], '=')
			&& ft_strcmp(root->cmd->argv[0], "export") != 0))
			add_env(root, root->cmd->argv[i], VAR);
		i++;
	}
}
