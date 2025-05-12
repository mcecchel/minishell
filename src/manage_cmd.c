/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/05/08 15:37:01 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*find_env_path(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "PATH=", 5) == 0)
			return (shell->envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	is_valid_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd == NULL || *cmd == '\0' || find_spaces(*cmd) == 1)
	{
		perror("Error: Invalid command");
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

char	*get_cmd_path(t_shell *shell, t_cmd *cmd)
{
	char	**paths;
	char	*full_path;

	if (!is_valid_command(shell, cmd))
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = get_paths(shell);
	if (!paths)
		return (NULL);
	full_path = search_command(paths, cmd);
	return (full_path);
}

void    execute_cmd(t_shell *shell, char *cmd_line);
