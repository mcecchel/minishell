/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:45:25 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 15:37:08 by mbrighi          ###   ########.fr       */
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

int	check_export(t_shell *shell, char *arg)
{
	int i;

	i = 0;
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
	{
		fd_printf(2, "Invalid argument to export\n");
		shell->exit_value = 1;
		return (1);
	}
	while (arg[i] != '\0')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]) && arg[i] != '=')
		{
			fd_printf(2, "Invalid argument to export\n");
			shell->exit_value = 1;
			return (1);
		}
		i++;
	}
	return (0);
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
		update_shell_envp(root);
		return ;
	}
	add_new_env(root, name, value, type);
	update_shell_envp(root);
}

void	where_it_goes(t_shell *root, t_cmd *cmd, int i)
{
	while (cmd->argv[i] != NULL)
	{
		if (ft_strchr(cmd->argv[i], '=') && check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], ENV);
		else if (check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], EXPORT);
		else if (ft_strchr(cmd->argv[i], '=')
			&& check_export(root, cmd->argv[i]) == 0)
			add_env(root, cmd->argv[i], VAR);
		i++;
	}
}

int	ft_export(t_shell *root, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	if (ft_strcmp(cmd->argv[0], "export") == 0)
		i = 1;
	if (cmd->argc == 1)
	{
		fd = which_fd(root);
		print_env_list_fd(root->env, EXPORT, fd);
		return (0);
	}
	where_it_goes(root, cmd, i);
	return (root->exit_value);
}
