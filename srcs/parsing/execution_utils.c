/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:54:41 by mbrighi           #+#    #+#             */
/*   Updated: 2025/08/01 17:30:50 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error_handler(t_shell *shell, t_cmd *cmd, int err, int exit_code)
{
	if (err == 0)
		fd_printf(2, "dup2 error");
	if (err == 1)
		fd_printf(2, "Execve failed");
	if (err == 2)
		fd_printf(2, "Error dup2 prev_pipe");
	if (err == 3)
		fd_printf(2, "dup2 pipe_out");
	if (cmd)
		close_cmd_fds(cmd);
	else
		close_cmd_fds(shell->cmd);
	cleanup_shell(shell);
	clean_exit(shell);
	exit (exit_code);
}

int	is_directory(char *path)
{
	int	is_a_folder;

	is_a_folder = open(path, __O_DIRECTORY);
	if (is_a_folder != -1)
		return (close (is_a_folder), 1);
	close (is_a_folder);
	return (0);
}

void	execve_failed(t_shell *shell, t_cmd *cmd, char *path)
{
	int	status_code;

	if (access(path, F_OK) != 0)
		status_code = 127;
	else if (access(path, X_OK) != 0)
		status_code = 126;
	else if (is_directory(path))
		status_code = 126;
	else
		status_code = 1;
	free(path);
	fork_error_handler(shell, cmd, 1, status_code);
}

void	print_envp_char(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
	{
		printf("envp is NULL\n");
		return ;
	}
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
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
			free_matrix(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}
