/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrighi <mbrighi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/06/18 19:19:00 by mbrighi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Funzione per gestire gli errori di esecuzione
void	handle_exec_error(t_cmd *cmd, char **command, char *path)
{
	free_split(command);
	free(path);
	close_cmd_fds(cmd);
	exit(1);
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
	{
		free_env_list(shell->env);
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
	free_env_list(shell->env);
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

