/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:22:07 by mbrighi           #+#    #+#             */
/*   Updated: 2025/07/15 16:36:55 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *env, char *to_change)
{
	while (env)
	{
		if (env->var && ft_strcmp(env->var, to_change) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	change_env(t_shell *root, char *old_path, char *current_path)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = find_env(root->env, "PWD");
	if (pwd)
	{
		if (pwd->arg)
			free(pwd->arg);
		pwd->arg = ft_strdup(current_path);
	}
	oldpwd = find_env(root->env, "OLDPWD");
	if (oldpwd)
	{
		if (oldpwd->arg != NULL)
			free(oldpwd->arg);
		oldpwd->arg = ft_strdup(old_path);
		oldpwd->ex_env = 1;
	}
	update_shell_envp(root);
}

static char	*get_target_path(t_shell *root)
{
	t_env	*home;

	if (!root->cmd->argv[1])
	{
		home = find_env(root->env, "HOME");
		if (!home || !home->arg)
		{
			fd_printf(2,"cd: HOME not set\n");
			return (NULL);
		}
		return (home->arg);
	}
	else
		return (root->cmd->argv[1]);
}

static int	change_directory(const char *target_path)
{
	if (chdir(target_path) == -1)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *root, t_cmd *cmd)
{
	char	*current_path;
	char	*old_path;
	char	*target_path;

	if (cmd->argc > 2)
	{
		fd_printf(2, "bash: cd: too many arguments\n");
		return (root->exit_value = 1, 1);
	}
	target_path = get_target_path(root);
	if (!target_path)
		return (1);
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (1);
	if (change_directory(target_path))
	{
		free(old_path);
		return (1);
	}
	current_path = getcwd(NULL, 0);
	change_env(root, old_path, current_path);
	free(current_path);
	free(old_path);
	return (0);
}
