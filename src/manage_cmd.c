/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/05/21 17:56:10 by mcecchel         ###   ########.fr       */
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

// Funzione per liberare matrice di stringhe
void	free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	close_cmd_fds(t_cmd *cmd)
{
	if (cmd->infile != -1)
	{
		close(cmd->infile);
		cmd->infile = -1;
	}
	if (cmd->outfile != -1)
	{
		close(cmd->outfile);
		cmd->outfile = -1;
	}
}

int	is_valid_command(t_cmd *cmd, char *command)
{
	if (command == NULL || *command == '\0' || is_space(*command) == 1)
	{
		perror("Error: Invalid command");
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
	return (full_path);
}

// Funzione per gestire gli errori di esecuzione
void	handle_exec_error(t_cmd *cmd, char **command, char *path)
{
	free_split(command);
	free(path);
	close_cmd_fds(cmd);
	// Funzione per chiudere le pipe tra comandi
	exit(1);
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
	{
		close_cmd_fds(cmd);
		exit(1);
	}
	// Gestione delle redirezioni
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			free(path);
			close_cmd_fds(cmd);
			exit(1);
		}
	}
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			free(path);
			close_cmd_fds(cmd);
			exit(1);
		}
	}
	execve(path, cmd->argv, shell->envp);
	perror("Execve failed");
	free(path);
	close_cmd_fds(cmd);
	exit(1);
}

// Nuova funzione per eseguire la lista di comandi con pipe
void	execute_command_list(t_shell *shell)
{
	t_cmd	*current;
	int		fd_pipe[2];
	int		prev_pipe;

	current = shell->cmd;
	prev_pipe = -1;

	while (current)
	{
		// Se non è l'ultimo comando, crea una pipe
		if (current->next)
		{
			if (pipe(fd_pipe) == -1)
			{
				perror("pipe");
				return;
			}
		}
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("fork");
			return;
		}
		if (current->pid == 0)// Processo figlio
		{
			// Collega l'input alla pipe precedente se esiste
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			// Se non è l'ultimo comando, collega l'output alla nuova pipe
			if (current->next)
			{
				close(fd_pipe[0]);
				// Se non c'è già un output specificato, usa la pipe
				if (current->outfile == -1)
					dup2(fd_pipe[1], STDOUT_FILENO);
				close(fd_pipe[1]);
			}
			execute_cmd(shell, current);
			// NB : non dovremmo mai arrivare qui
			exit(1);
		}
		else// Processo padre
		{
			// Chiudi la pipe precedente se esiste
			if (prev_pipe != -1)
				close(prev_pipe);
			// Se non è l'ultimo comando, aggiorna prev_pipe
			if (current->next)
			{
				close(fd_pipe[1]);
				prev_pipe = fd_pipe[0];
			}
			current = current->next;
		}
	}
	// Aspetta che tutti i processi figli terminino
	current = shell->cmd;
	while (current)
	{
		if (current->pid > 0)
			waitpid(current->pid, NULL, 0);
		current = current->next;
	}
	// Chiudi l'ultima pipe se esiste
	if (prev_pipe != -1)
		close(prev_pipe);
}
