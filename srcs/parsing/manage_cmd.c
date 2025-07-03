/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcecchel <mcecchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:09:38 by marianna          #+#    #+#             */
/*   Updated: 2025/07/03 18:33:34 by mcecchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_error_handler(t_shell *shell, char *path, int a)
{	if (a == 0)
		perror("dup2 error");
	cleanup_shell(shell);
	free_env_list(shell->env);
	free_split(shell->envp);
	if (path)
		free(path);
	close_cmd_fds(shell->cmd);
	exit(1);
}

// Funzione per gestire gli errori di esecuzione
void	handle_exec_error(t_shell *shell, char **command, char *path)
{
	free_split(command);
	if (path)
		free(path);
	close_cmd_fds(shell->cmd);
	exit(1);
}

void	execute_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = get_cmd_path(shell, cmd, cmd->argv[0]);
	if (!path)
		exit(127); // Command not found
	// Gestione redirezioni INPUT
	if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, STDIN_FILENO) == -1)
		{
			perror("Error in dup2 input");
			free(path);
			close_cmd_fds(cmd);
			exit(1);
		}
		close(cmd->infile);
	}
	// Gestione redirezioni OUTPUT
	if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			free(path);
			close_cmd_fds(cmd);
			exit(1);
		}
		close(cmd->outfile); // IMPORTANTE: chiudi dopo dup2
	}
	execve(path, cmd->argv, shell->envp);
	perror("Execve failed");
	free(path);
	close_cmd_fds(cmd);
	exit(1);
}

void	print_envp_char(char **envp)
{
	int i = 0;
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
				perror("Pipe error");
				return;
			}
		}
		current->pid = fork();
		if (current->pid == -1)
		{
			perror("Fork error");
			return;
		}
		if (current->pid == 0) // Processo figlio
		{
			// Collega l'input alla pipe precedente se esiste
			if (prev_pipe != -1)
			{
				if (dup2(prev_pipe, STDIN_FILENO) == -1)
				{
					perror("Error dup2 prev_pipe");
					exit(1);
				}
				close(prev_pipe);
			}
			// Se non è l'ultimo comando, collega l'output alla nuova pipe
			if (current->next)
			{
				close(fd_pipe[0]);
				
				// Solo se non c'è già una redirezione di output
				if (current->outfile == -1)
				{
					if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
					{
						perror("dup2 pipe_out");
						exit(1);
					}
				}
				close(fd_pipe[1]); // Chiudi write end
			}
			execute_cmd(shell, current);
			exit(1);// NB: on dovremmo mai arrivare qui
		}
		else // Processo padre
		{
			// Chiudi la pipe precedente se esiste
			if (prev_pipe != -1)
				close(prev_pipe);
			// Se non è l'ultimo comando, aggiorna prev_pipe
			if (current->next)
			{
				close(fd_pipe[1]); // Chiudi write end
				prev_pipe = fd_pipe[0]; // Salva read end
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
