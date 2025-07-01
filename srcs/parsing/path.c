/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:21:50 by mcecchel          #+#    #+#             */
/*   Updated: 2025/07/01 13:17:05 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env_path(t_shell *shell)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (env->var && ft_strcmp(env->var, "PATH") == 0)
			return (env->arg);
		env = env->next;
	}
	return (NULL);
}

int	is_valid_command(t_cmd *cmd, char *command)
{
	if (command == NULL || *command == '\0' || is_space(*command) == 1)
	{
		perror("Error: Invalid command12");
		if (cmd->infile != -1)
			close(cmd->infile);
		if (cmd->outfile != -1)
			close(cmd->outfile);
		return (0);
	}
	return (1);
}

char	**get_paths(t_shell *shell)
{
	char	*path_env;
	char	**paths;

	path_env = find_env_path(shell);
	if (!path_env)
	{
		perror("Error: Failed to find path");
		return (NULL);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		perror("Error: Failed to split path");
	return (paths);
}

char	*search_command(char **paths, char *cmd)
{
	char	*temp;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(t_shell *shell, t_cmd *cmd, char *command)
{
	char	**paths;
	char	*full_path;

	if (!is_valid_command(cmd, command))
		return (NULL);
	if (access(command, F_OK | X_OK) == 0 && ft_strchr(command, '/'))
		return (ft_strdup(command));
	paths = get_paths(shell);
	if (!paths)
		return (NULL);
	full_path = search_command(paths, command);
	if (!full_path)
	{
		perror("Errors: Command not found");
		free_split(paths);
		free_split(shell->envp);
		close_cmd_fds(cmd);
		cleanup_shell(shell);
		free_env_list(shell->env);
		return (NULL);
	}
	return (full_path);
}
